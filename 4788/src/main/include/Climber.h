#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

using actState = wml::actuators::BinaryActuatorState;

enum class ClimberState {
  DOWN,
  MANUAL
};

class Climber : public wml::StrategySystem {
 public:
  Climber(wml::Gearbox &climberLeftGearbox, 
          wml::Gearbox &climberRightGearbox,
          wml::actuators::DoubleSolenoid &climberActuator) :
          _climberLeftGearbox(climberLeftGearbox),
          _climberRightGearbox(climberRightGearbox),
          _climberActuator(climberActuator) {}

  void SetClimber(const ClimberState st, double setpointL, double setpointR) {
    _climberState = st;
    _climberLsetpoint = setpointL;
    _climberRsetpoint = setpointR;
  }

  ClimberState GetClimberState() {
    return _climberState;
  }

  void UpdateClimber(double dt) {
    double voltageL = 0;
    double voltageR = 0;
    switch (_climberState) {
      case ClimberState::DOWN:
        voltageL = 0;
        voltageR = 0;
        _climberActuator.SetTarget(actState::kForward);
       break;

      case ClimberState::MANUAL:
        voltageL = 12 * _climberLsetpoint;
        voltageR = 12 * _climberRsetpoint;
        _climberActuator.SetTarget(actState::kReverse);
       break;
    }
    _climberLeftGearbox.transmission->SetVoltage(voltageL);
    _climberRightGearbox.transmission->SetVoltage(voltageR);
    _climberActuator.Update(dt);
  }

  void Update(double dt) {
    UpdateClimber(dt);
  }
 
 private:
  // Gearboxes
  wml::Gearbox &_climberLeftGearbox, &_climberRightGearbox;
  wml::actuators::DoubleSolenoid &_climberActuator;

  // States
  ClimberState _climberState{ClimberState::DOWN};

  // Setpoints
  double _climberLsetpoint = 0, _climberRsetpoint = 0;
};