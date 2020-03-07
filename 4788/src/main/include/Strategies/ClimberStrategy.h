#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Climber.h"

using ButtonState = wml::controllers::Controller;

class ClimberManualStrategy : public wml::Strategy {
 public:
  ClimberManualStrategy(
    Climber &climber,
    wml::controllers::SmartControllerGroup &controllers
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

    if (_controllers.Get(ControlMap::ClimberToggle, ButtonState::ONRISE))
      ClimberToggled = !ClimberToggled;

    // Detect if climber is toggled
    if (ClimberToggled) {
      _climber.SetClimber(ClimberState::MANUAL, leftClimber_power, rightClimber_power);
    } else {
      _climber.SetClimber(ClimberState::DOWN, 0, 0);
    }
  }
 private:
  Climber &_climber;
  wml::controllers::SmartControllerGroup &_controllers;

  bool ClimberToggled = false;
};