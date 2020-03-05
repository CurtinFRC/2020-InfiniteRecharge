#pragma once

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

using actState = wml::actuators::BinaryActuatorState;

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
          wml::actuators::DoubleSolenoid &climberActuator) :
          _climberLeftGearbox(climberLeftGearbox),
          _climberRightGearbox(climberRightGearbox),
          _climberActuator(climberActuator) {}

  void SetClimberActuator(const ClimberActuatorState st) {
    _climberActuatorState = st;
  }

  void SetClimber(const ClimberState st, double setpointL, double setpointR) {
    _climberState = st;
    _climberLsetpoint = setpointL;
    _climberRsetpoint = setpointR;
  }

  /* When this goes down. Intake needs to come up first */
  void UpdateClimberActuator(double dt) {
    switch (_climberActuatorState) {
      case ClimberActuatorState::DOWN:
        _climberActuator.SetTarget(actState::kReverse);
       break;
      
      case ClimberActuatorState::UP:
        _climberActuator.SetTarget(actState::kForward);
       break;
    }
    _climberActuator.Update(dt);
  }

  void UpdateClimber(double dt) {
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
    _climberLeftGearbox.transmission->SetVoltage(voltageL);
    _climberRightGearbox.transmission->SetVoltage(voltageR);
  }

  void Update(double dt) {
    UpdateClimber(dt);
    UpdateClimberActuator(dt);
  }
 
 private:
  // Gearboxes
  wml::Gearbox &_climberLeftGearbox, &_climberRightGearbox;
  wml::actuators::DoubleSolenoid &_climberActuator;

  // States
  ClimberState _climberState{ClimberState::IDLE};
  ClimberActuatorState _climberActuatorState{ClimberActuatorState::DOWN};

  // Setpoints
  double _climberLsetpoint = 0, _climberRsetpoint = 0;
};