#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

using actState = wml::actuators::BinaryActuatorState;

enum class TurretRotationState {
  IDLE,
  ZEROING,
  MANUAL,
  PID
};

enum class TurretAngleState {
  IDLE,
  ZEROING,
  MANUAL,
  PID
};

enum class TurretFlywheelState {
  IDLE,
  MANUAL,
  AUTO
};


class Turret : public wml::StrategySystem {
 public:
  Turret(wml::Gearbox &turretRotationGearbox,
         wml::Gearbox &turretAngleGearbox,
         wml::Gearbox &flywheelGearbox,
         wml::sensors::LimitSwitch &rotZeroSensor,
         wml::sensors::LimitSwitch &angleZeroSensor) :
         _turretRotationGearbox(turretRotationGearbox),
         _turretAngleGearbox(turretAngleGearbox),
         _flywheelGearbox(flywheelGearbox),
         _rotZeroSensor(rotZeroSensor),
         _angleZeroSensor(angleZeroSensor) {}
  
  // Set the Turrets Subsystems
  void SetTurretRotation(const TurretRotationState st, double setpoint) {
    _turretRotationState = st;
    _rotationSetpoint = setpoint;
  }

  void SetTurretAngle(const TurretAngleState st, double setpoint) {
    _turretAngleState = st;
    _angleSetpoint = setpoint;
  }

  void SetTurretFlywheel(const TurretFlywheelState st, double setpoint) {
    _turretFlywheelState = st;
    _flywheelSetpoint = setpoint;
  }

  void UpdateTurretRotation(double dt) {
    double voltage = 0;
    switch (_turretRotationState) {
      case TurretRotationState::IDLE:
        voltage = 0;
       break;

      case TurretRotationState::MANUAL:
        voltage = 12 * _rotationSetpoint;
       break;
      
      case TurretRotationState::PID:
        voltage = 12 * _rotationSetpoint;
       break;
      
      case TurretRotationState::ZEROING:
        if (!_rotZeroSensor.Get()) {
          voltage = 12 * 0.12;
        } else {
          _turretRotationGearbox.encoder->ZeroEncoder();
          TurretZeroed = true;
          SetTurretRotation(TurretRotationState::IDLE, 0);
        }
       break;
    }
    _turretRotationGearbox.transmission->SetVoltage(voltage);
  }


  void UpdateTurretAngle(double dt) {
    double voltage = 0;
    switch (_turretAngleState) {
      case TurretAngleState::IDLE:
        voltage = 0;
       break;

      case TurretAngleState::MANUAL:
        voltage = 12 * _angleSetpoint;
       break;

      case TurretAngleState::PID:
        voltage = 12 * _angleSetpoint;
       break;

      case TurretAngleState::ZEROING:
        if (!_angleZeroSensor.Get()) {
          voltage = 12 * -0.2;
        } else {
          _turretAngleGearbox.encoder->ZeroEncoder();
          AngleZeroed = true;
          SetTurretAngle(TurretAngleState::IDLE, 0);
        }
       break;
    }
    _turretAngleGearbox.transmission->SetVoltage(voltage);
  }

  void UpdateTurretFlywheel(double dt) {
    double voltage = 0;
    switch (_turretFlywheelState) {
      case TurretFlywheelState::IDLE:
        voltage = 0;
       break;

      case TurretFlywheelState::MANUAL:
        voltage = _flywheelSetpoint;
       break;

      case TurretFlywheelState::AUTO:
        voltage = _flywheelSetpoint;
       break;
    }
    _flywheelGearbox.transmission->SetVoltage(voltage);
  }

  void Update(double dt) {
    UpdateTurretRotation(dt);
    UpdateTurretAngle(dt);
    UpdateTurretFlywheel(dt);
  }

  // Gearboxes
  wml::Gearbox &_turretRotationGearbox, &_turretAngleGearbox, &_flywheelGearbox;

  // Sensors
  wml::sensors::LimitSwitch &_rotZeroSensor, &_angleZeroSensor;

  bool TurretZeroed = false;
  bool AngleZeroed = false;

 private:
  // States
  TurretRotationState _turretRotationState{TurretRotationState::IDLE};
  TurretAngleState _turretAngleState{TurretAngleState::IDLE};
  TurretFlywheelState _turretFlywheelState{TurretFlywheelState::IDLE};

  // Setpoints
  double _rotationSetpoint = 0, _angleSetpoint = 0, _flywheelSetpoint = 0;
};