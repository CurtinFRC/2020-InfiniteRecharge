#pragma once 

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

using actState = wml::actuators::BinaryActuatorState;

enum class IntakeState {
  IDLE,
  MANUAL,
  AUTO
};

enum class IntakeActuatorState {
  DEPLOYED,
  STOWED
};

class Intake : public wml::StrategySystem {
 public:
  Intake(wml::Gearbox &intakeGearbox,
          wml::actuators::DoubleSolenoid &intakeActuator);

  void SetIntakeActuator(const IntakeActuatorState st) {
    _intakeActuatorState = st;
  }

  void SetIntake(const IntakeState st, double setpoint) {
    _intakeState = st;
    _intakeSetpoint = setpoint;
  }

  void UpdateIntakeActuator(double dt) {
    switch (_intakeActuatorState) {
      case IntakeActuatorState::STOWED:
        _intakeActuator.SetTarget(actState::kReverse);
       break;

      case IntakeActuatorState::DEPLOYED:
        _intakeActuator.SetTarget(actState::kForward);
       break;
    }
    _intakeActuator.Update(dt);
  }

  void UpdateIntake(double dt) {
    double voltage = 0;
    switch (_intakeState) {
      case IntakeState::IDLE:
        voltage = 0;
       break;
      
      case IntakeState::MANUAL:
        voltage = 12 * _intakeSetpoint;
       break;

      case IntakeState::AUTO:
        voltage = 12 * _intakeSetpoint;
    }
    _intakeGearbox.transmission->SetVoltage(voltage);
  }

  void Update(double dt) {
    UpdateIntake(dt);
    UpdateIntakeActuator(dt);
  }

 private:
  // Gearboxes
  wml::Gearbox &_intakeGearbox;
  wml::actuators::DoubleSolenoid &_intakeActuator;

  // States
  IntakeState _intakeState{IntakeState::IDLE};
  IntakeActuatorState _intakeActuatorState{IntakeActuatorState::STOWED};

  // Setpoints
  double _intakeSetpoint;
};