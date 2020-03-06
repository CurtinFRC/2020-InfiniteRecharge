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

  // Schedule Gains
  double ScheduleGains(double dt) {
    if (abs(targetX) < (abs(imageWidth)/8)) {
      dt = 0.5; // Make accumulator awesome baby
      kP = &RkP3;
      kI = &RkI3;
      kD = &RkD3;
    } else if (abs(targetX) < (abs(imageWidth)/6)) {
      kP = &RkP2;
      kI = &RkI2;
      kD = &RkD2;
    } else {
      kP = &RkP;
      kI = &RkI;
      kD = &RkD;
    }
    return dt;
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

  // y=mx+b (y in this case is encoder value)
  // double m =  0.0002214286;
  // double b = 0.0951786;
  // double yIntercept = -429.839;
  // double xIntercept = 0.0951786;

  double YAutoAimCalc(double dt, double targetY) {

    // Calculate goal
    double EC = ECvalue2 - ECvalue1;
    double YV = Yvalue2 - Yvalue1;
    double Gradient = (EC/YV);

    double Intercept = (ECvalue1 - (Gradient * Yvalue1));
    double Goal = ((Gradient * targetY) + Intercept);

    // Calculate PID
    double input = _turret._turretAngleGearbox.encoder->GetEncoderRotations();

    double error = Goal - input;

    double derror = (error - ApreviousError) / dt;
    Asum = Asum + error * dt;

    double output;
    output = AkP * error + AkI * Asum + AkD * derror;


    _table->PutNumber("AngleDError", derror);
    _table->PutNumber("AngleError", error);
    _table->PutNumber("AngleDelta Time", dt);
    _table->PutNumber("AngleOutput", output);

    ApreviousError = Aerror;


    return output;
  }

  // X Auto Aim Algorithm
  double XAutoAimCalc(double dt, double targetX)  {
    double TurretFullRotation = (ControlMap::TurretRatio * ControlMap::TurretGearBoxRatio);
    Rotations2FOV = (TurretFullRotation/ControlMap::CamFOV);
    double targetXinRotations = targetX * (Rotations2FOV/imageWidth);

    RotGoal = _turret._turretRotationGearbox.encoder->GetEncoderRotations() + targetXinRotations;

    dt = ScheduleGains(dt);
    double input = _turret._turretRotationGearbox.encoder->GetEncoderRotations();

    // Calculate PID
    double Rerror = RotGoal - input;

    double derror = (Rerror - RpreviousError) / dt;
    Rsum = Rsum + Rerror * dt;

    double output;
    output = *kP * Rerror + *kI * Rsum + *kD * derror;


    _table->PutNumber("RoationDError", derror);
    _table->PutNumber("RotationError", Rerror);
    _table->PutNumber("RotationDelta Time", dt);
    _table->PutNumber("RotationOutput", output);

    RpreviousError = Rerror;
    return output;
  }


  void OnUpdate(double dt) override {
    targetX = _table->GetNumber("Target_X", 0);
    targetY = _table->GetNumber("Target_Y", 0);

    imageHeight = _table->GetNumber("ImageHeight", 0); 
    imageWidth = _table->GetNumber("ImageWidth", 0);

    double turretRotation_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::TurretManualRotate));
    turretRotation_power *= ControlMap::MaxTurretSpeed;
    double turretAngle_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::TurretManualAngle));
    turretAngle_power *= ControlMap::MaxTurretAngularSpeed;
    double turretFlywheel_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::TurretFlyWheelSpinUp));

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

  // PID scheduled values
  // Schedule 1 (Get to location)
  double RkP = 0.05; // 0.899
  double RkI = 0; // 0.107
  double RkD = 0.001; // 0.036
  // Schedule 2 (Precise locate target)
  double RkP2 = 0.07; // N/A
  double RkI2 = 0.001; // N/A
  double RkD2 = 0.001; // N/A
  // Schedule 3 (Lock on target)
  double RkP3 = 0.1; // N/A
  double RkI3 = 0.003; // N/A
  double RkD3 = 0.001; // N/A

  // Pointed Gains I AM GAINS
  double *kP;
  double *kI;
  double *kD;

  double RotGoal = 0;
  double Rsum = 0;
  double RpreviousError = 0;


  // Angle Cals
  double AkP = 20;
  double AkI = 0;
  double AkD = 0;

  double Aerror;

  double Asum = 0;
  double ApreviousError = 0;
  double AGoal = 0;

  // Setpoint 1
  double Yvalue1 = 85;
  double ECvalue1 = 0.114;
  // Setpoint 2
  double Yvalue2 = 225;
  double ECvalue2 = 0.145;
  

  bool ClimberToggled = false;
};