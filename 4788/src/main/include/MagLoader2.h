#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

enum class MagLoaderState {
  AUTO,
  SHIFT,
  MANUAL,
  FIRE
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
      case MagLoaderState::AUTO:
        if (_stopSensor.GetAverageValue() >= ControlMap::MagazineBallThreshFinal) 
          voltage = 0;
        else if (_indexSensor.GetAverageValue() >= ControlMap::MagazineBallThreshIndex)
          voltage = 0;
        else if (_startSensor.GetAverageValue() >= ControlMap::MagazineBallThreshStart)
          voltage = 12 * _magLoaderSetpoint;
        else 
          voltage = 0;
       break;
      
      case MagLoaderState::SHIFT:
        if((_stopSensor.GetAverageValue() <= ControlMap::MagazineBallThreshFinal) && (_indexSensor.GetAverageValue() <= ControlMap::MagazineBallThreshIndex))
          voltage = 12 * _magLoaderSetpoint;
        else 
          voltage = 0;
       break;

      case MagLoaderState::MANUAL:
        voltage = 12 * _magLoaderSetpoint;
       break;

      case MagLoaderState::FIRE:
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
  MagLoaderState _magLoaderState{MagLoaderState::AUTO};

  // Setpoints
  double _magLoaderSetpoint = 0;
};