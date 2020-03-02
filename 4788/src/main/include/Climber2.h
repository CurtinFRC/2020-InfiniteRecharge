#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

enum class ClimberState {
  IDLE,
  MANUAL
};

class Climber : public wml::StrategySystem {
 public:
  Climber(wml::Gearbox &climberLeftGearbox, 
          wml::Gearbox &climberRightGearbox,
          wml::actuators::DoubleSolenoid &climberActuator);

  void SetClimber(const ClimberState st, double setpointL, double setpointR) {
    _climberState = st;
    _climberLSetpoint = setpointL;
    _climberRSetpoint = setpointR;
  }

  UpdateClimber(double dt) {
    double voltageL = 0;
    double voltageR = 0;
    switch (_climberState) {
      case ClimberState::IDLE:
        voltageL = 0;
        voltageR = 0;
        _climberActuator.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
       break;

      case ClimberState::MANUAL:
        voltageL = 12 * _climberLsetpoint;
        voltageR = 12 * _climberRsetpoint;
        _climberActuator.Settarget(wml::actuators::BinaryActuatorState::kForward);
    }
  }

  void Update(double dt) {
    UpdateClimber(dt);
  }
 
 private:
  wml::Gearbox &_climberLeftGearbox, &_climberRightGearbox;
  wml::actuators::DoubleSolenoid &_climberActuator;

  ClimberState _climberState{ClimberState::IDLE};

  double _climberLsetpoint = 0, _climberRsetpoint = 0;
}