#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

enum class MagLoaderState {
  IDLE,
  MANUAL,
  SHIFTUP,
  SHIFTDOWN,
  FIRE,
  AUTO
};

class MagLoader : public wml::StrategySystem {
 public:
  MagLoader(wml::Gearbox &magLoaderGearbox,
            frc::AnalogInput &startSensor,
            frc::AnalogInput &indexSensor,
            frc::AnalogInput &stopSensor);

  void SetMagLoader(const MagLoaderState st, double setpoint) {
    _magLoaderState = st;
    _magLoaderSetpoint = setpoint;
  }

  void UpdateMagLoader(double dt) {
    double voltage = 0;
    switch (_magLoaderState) {
      case MagLoaderState::IDLE:
        voltage = 0;
       break;
      
      case MagLoaderState::MANUAL:
        voltage = 12 * _magLoaderSetpoint;
       break;

      case MagLoaderState::SHIFTUP:
        voltage = 12 * _magLoaderSetpoint;
       break;

      case MagLoaderState::SHIFTDOWN:
        voltage = 12 * _magLoaderSetpoint;
       break;

      case MagLoaderState::AUTO:
        voltage = 12 * _magLoaderSetpoint;
       break;
    }
    _magLoaderGearbox.transmission->SetVoltage(voltage);
  }

  void Update(double dt) {
    UpdateMagLoader(dt);
  }
 
 private:
  // Gearboxes
  wml::Gearbox &_magLoaderGearbox;
  frc::AnalogInput &_startSensor;
  frc::AnalogInput &_indexSensor;
  frc::AnalogInput &_stopSensor;

  // States
  MagLoaderState _magLoaderState{MagLoaderState::IDLE};

  // Setpoints
  double _magLoaderSetpoint = 0;
};