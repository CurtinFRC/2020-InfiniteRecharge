#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

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
         wml::sensors::LimitSwitch &angleZeroSensor);
  
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
        voltage = 12 * _rotationSetpoint;
       break;
    }
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
        voltage = 12 * _angleSetpoint;
       break;
    }
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
  }

 private:
  // Gearboxes
  wml::Gearbox &_turretRotationGearbox, &_turretAngleGearbox, &_flywheelGearbox;

  // Sensors
  wml::sensors::LimitSwitch &_rotZeroSensor, &_angleZeroSensor;

  // States
  TurretRotationState _turretRotationState{TurretRotationState::IDLE};
  TurretAngleState _turretAngleState{TurretAngleState::IDLE};
  TurretFlywheelState _turretFlywheelState{TurretFlywheelState::IDLE};

  // Setpoints
  double _rotationSetpoint = 0, _angleSetpoint = 0, _flywheelSetpoint = 0;
};