#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

enum class ClimberState {
  IDLE,
  MANUAL
};

enum class ClimberActuatorState {
  DOWN,
  UP
};

class Climber : public wml::StrategySystem {
 public:
  Climber(wml::Gearbox &climberLeftGearbox, 
          wml::Gearbox &climberRightGearbox,
          wml::actuators::DoubleSolenoid &climberActuator);

  void SetClimber(const ClimberState st, double setpointL, double setpointR) {
    _climberState = st;
    _climberLsetpoint = setpointL;
    _climberRsetpoint = setpointR;
  }

  /* When this goes down. Intake needs to come up first */
  UpdateClimberActuator(double dt) {
    switch (_climberActuatorState) {
      case ClimberActuatorState::DOWN:
        _climberActuator.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
       break;
      
      case ClimberActuatorState::UP:
        _climberActuator.SetTarget(wml::actuators::BinaryActuatorState::kForward);
       break;
    }
  }

  UpdateClimber(double dt) {
    double voltageL = 0;
    double voltageR = 0;
    switch (_climberState) {
      case ClimberState::IDLE:
        voltageL = 0;
        voltageR = 0;
       break;

      case ClimberState::MANUAL:
        voltageL = 12 * _climberLsetpoint;
        voltageR = 12 * _climberRsetpoint;
       break;
    }
  }

  void Update(double dt) {
    UpdateClimber(dt);
    UpdateClimberActuator(dt);
  }
 
 private:
  wml::Gearbox &_climberLeftGearbox, &_climberRightGearbox;
  wml::actuators::DoubleSolenoid &_climberActuator;

  ClimberState _climberState{ClimberState::IDLE};
  ClimberActuatorState _climberActuatorState{ClimberActuatorState::DOWN};

  double _climberLsetpoint = 0, _climberRsetpoint = 0;
}