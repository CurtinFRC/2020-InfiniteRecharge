#pragma once

#include "strategy/StrategySystem.h"

#include "RobotMap.h"

enum class TurretRotationState {
  IDLE,
  ZEROING,
  MANUAL,
  PID
};

enum class TurretFlywheelState {
  IDLE,
  MANUAL,
  PID,
};

class Turret : public wml::StrategySystem {
 public:
  Turret(wml::Gearbox &rotationGearbox,
         wml::Gearbox &hoodGearbox,
         wml::Gearbox &flywheelGearbox,
         wml::sensors::BinarySensor &leftLimit,
         wml::sensors::BinarySensor &angleDownLimit,
         std::shared_ptr<nt::NetworkTable> &visionTable,
         std::shared_ptr<nt::NetworkTable> &rotationTable);

  void SetRotation(const TurretRotationState st, double setpoint) {
    _rotState = st;
    _rotSetpoint = setpoint;
  }

  void SetFlywheel(const TurretFlywheelState st, double setpoint) {
    _flywheelState = st;
    _flywheelSetpoint = setpoint;
  }

  void UpdateRotation(double dt) {
    double voltage = 0;
    switch(_rotState) {
      case TurretRotationState::IDLE:
        voltage = 0;
        break;
      case TurretRotationState::ZEROING:
        /* ... */
        break;
      case TurretRotationState::MANUAL:
        voltage = 12 * _rotSetpoint;
        break;
      case TurretRotationState::PID:
        voltage = /* PID LOGIC */;
        break;
      /* .. */
    }
    _rotationGearbox.transmission->SetVoltage(voltage);
  }

  void UpdateFlywheel(double dt) {
    double voltage = 0;
    switch(_flywheelState) {
      /* .. */
    }
    _flywheelGearbox.transmission->SetVoltage(voltage);
  }

  void Update(double dt) {
    UpdateRotation(dt);
    UpdateFlywheel(dt);
  }

 private:
  wml::Gearbox &_rotationGearbox, &_hoodGearbox, &_flywheelGearbox;
  wml::sensors::BinarySensor &_leftLimit, &_rightLimit;
  std::shared_ptr<nt::NetworkTable> &_visionTable, &_rotationTable;

  TurretRotationState _rotState{TurretRotationState::MANUAL};
  TurretFlywheelState _flywheelState{TurretFlywheelState::MANUAL};

  double _rotSetpoint = 0, _flywheelSetpoint = 0;
};