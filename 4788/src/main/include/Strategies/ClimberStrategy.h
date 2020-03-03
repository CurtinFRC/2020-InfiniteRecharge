#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Climber.h" // Meant to be climber2.h

using ButtonState = wml::controllers::Controller;

frc::Timer climbTime;

class ClimberManualStrategy : wml::Strategy {
 public:
  ClimberManualStrategy(
    const Climber &climber,
    const wml::controllers::SmartControllerGroup &controllers
  ) : wml::Strategy("Manual"), _climber(climber), _controllers(controllers) {
    Requires(&climber);
    SetCanBeInterrupted(true);
    SetCanBeReused(true);
  }

  void OnUpdate(double dt) override {
    double leftClimber_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::ClimberControlLeft));
    leftClimber_power *= ControlMap::LiftMaxSpeed;
    double rightClimber_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::ClimberControlRight));
    rightClimber_power *= ControlMap::LiftMaxSpeed;

    if (_controllers.Get(ControlMap::ClimberToggle, ButtonState::ONRISE)) {
      if (ClimberToggled)
        ClimberToggled = false;
      else
        ClimberToggled = true;
    }

    if (ClimberToggled) {
      if (climbTime.Get() > 1) {
        _climber.SetClimber(ClimberState::MANUAL, leftClimber_power, rightClimber_power);
        _climber.SetClimberActuator(ClimberActuatorState::DOWN);
        climbTime.Reset();
        climbTime.Stop();
      } else {
        _climber.SetClimber(ClimberState::IDLE, leftClimber_power, rightClimber_power);
        _climber.SetClimberActuator(ClimberActuatorState::UP);
      }
    }
  }
 private:
  const Climber &_climber;
  const wml::controllers::SmartControllerGroup &_controllers;

  bool ClimberToggled = false;
};