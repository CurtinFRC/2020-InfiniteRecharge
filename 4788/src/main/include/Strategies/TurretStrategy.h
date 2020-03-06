#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "Turret2.h" // meant to be turret2.h

using ButtonState = wml::controllers::Controller;

class TurretManualStrategy : public wml::Strategy {
 public:
  TurretManualStrategy(
    Turret &turret,
    wml::controllers::SmartControllerGroup &controllers
  ) : wml::Strategy("Manual"), _turret(turret), _controllers(controllers) {
    Requires(&turret);
    SetCanBeInterrupted(true);
    SetCanBeReused(true);

    auto inst = nt::NetworkTableInstance::GetDefault();
    _visionTable = inst.GetTable("VisionTracking");
    _table = _visionTable->GetSubTable("Target");

    imageHeight = _table->GetNumber("ImageHeight", 0); 
    imageWidth = _table->GetNumber("ImageWidth", 0); 
  }


  // Feedback for correct flywheel speeds
  void ContFlywheelFeedback() {
    if (_turret._flywheelGearbox.encoder->GetEncoderAngularVelocity() <= ControlMap::FlyWheelVelocity) {
      _controllers.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 1);
      _controllers.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 1);
    } else {
      _controllers.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 0);
      _controllers.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 0);
    }
  }

  // Flywheel Auto Spinup to velocity
  double FlyWheelAutoSpinup(double FlywheelPower) {
    if (_turret._flywheelGearbox.encoder->GetEncoderAngularVelocity() <= ControlMap::FlyWheelVelocity) {
      FlywheelPower += _turret._flywheelGearbox.encoder->GetEncoderAngularVelocity() < ControlMap::FlyWheelVelocity ? 0.05 : 0;
    }
    return FlywheelPower;
  }


  double YAutoAimCalc(double dt, double targetY) {
    /** do stuff */
    return 0;
  }

  double RotGoal = 0;
  double Rsum = 0;
  // X Auto Aim Algorithm
  double XAutoAimCalc(double dt, double targetX)  {
    double TurretFullRotation = (ControlMap::TurretRatio * ControlMap::TurretGearBoxRatio);
    Rotations2FOV = (TurretFullRotation/ControlMap::CamFOV);
    double targetXinRotations = targetX * (Rotations2FOV/imageWidth);

    RotGoal = _RotationalAxis.encoder->GetEncoderRotations() + targetXinRotations;

    dt = ScheduleGains(dt);
    double input = _RotationalAxis.encoder->GetEncoderRotations();

    // Calculate PID
    double Rerror = RotGoal - input;

    double derror = (Rerror - RpreviousError) / dt;
    Rsum = Rsum + Rerror * dt;

    double output;
    output = *kP * Rerror + *kI * Rsum + *kD * derror;

    table->PutBoolean("Schedule 2 electric boogaloo", GainsSchedule2);


    table->PutNumber("RoationDError", derror);
    table->PutNumber("RotationError", Rerror);
    table->PutNumber("RotationDelta Time", dt);
    table->PutNumber("RotationOutput", output);

    RpreviousError = Rerror;
    return output;
  }


  void OnUpdate(double dt) override {
    targetX = table->GetNumber("Target_X", 0);
    targetY = table->GetNumber("Target_Y", 0);

    imageHeight = table->GetNumber("ImageHeight", 0); 
    imageWidth = table->GetNumber("ImageWidth", 0);

    double turretRotation_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::TurretManualRotate));
    turretRotation_power *= ControlMap::MaxTurretSpeed;
    double turretAngle_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::TurretManualAngle));
    turretAngle_power *= ControlMap::MaxTurretAngularSpeed;
    double turretFlywheel_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::TurretFlywheelSpinUp));

    // Detect if climber is toggled
    if (_controllers.Get(ControlMap::ClimberToggle, ButtonState::ONRISE)) {
      if (ClimberToggled) 
        ClimberToggled = false;
      else 
        ClimberToggled = true;
    }

    /**
     * MAIN TURRET CONTROL
     */
    if (!ClimberToggled) {
      // PID Control
      if (_controllers.Get(ControlMap::TurretAutoAim)) {
        _turret.SetTurretRotation(TurretRotationState::PID, turretRotation_power = XAutoAimCalc(dt, targetX));
        _turret.SetTurretAngle(TurretAngleState::PID, turretAngle_power = YAutoAimCalc(dt, targetY));
        if (_controllers.Get(ControlMap::TurretFlyWheelSpinUp))
          _turret.SetTurretFlywheel(TurretFlywheelState::AUTO, turretFlywheel_power = FlyWheelAutoSpinup(turretFlywheel_power));
        else 
          _turret.SetTurretFlywheel(TurretFlywheelState::IDLE, turretFlywheel_power);
      // Manual Control
      } else {
        if (ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::TurretManualRotate)))
          _turret.SetTurretRotation(TurretRotationState::MANUAL, turretRotation_power);
        if (ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::TurretManualAngle)))
          _turret.SetTurretAngle(TurretAngleState::MANUAL, turretAngle_power);
        if (ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::TurretFlyWheelSpinUp)))
          _turret.SetTurretFlywheel(TurretFlywheelState::MANUAL, turretFlywheel_power);
      }
    } else {
      _turret.SetTurretRotation(TurretRotationState::IDLE, turretRotation_power);
      _turret.SetTurretAngle(TurretAngleState::IDLE, turretAngle_power);
      _turret.SetTurretFlywheel(TurretFlywheelState::IDLE, turretFlywheel_power);
    }
  }


 private:
  Turret &_turret;
  wml::controllers::SmartControllerGroup &_controllers;
  frc::Timer turretTime;

  // NT
  std::shared_ptr<nt::NetworkTable>_visionTable;
  std::shared_ptr<nt::NetworkTable>_table;

  // NT values
  double targetX;
  double targetY;
  double imageHeight;
  double imageWidth;

  // Calculated values
  double Rotations2FOV;

  bool ClimberToggled = false;
};