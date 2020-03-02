#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Climber.h"

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
    double rightClimber_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::ClimberControlRight));

    if (_controllers.Get(ControlMap::ClimberToggle)) {
      if (ClimberToggled) {
        
        ClimberToggled = false;
      }
    }
  }
 private:
  const Climber &_climber;
  const wml::controllers::SmartControllerGroup &_controllers;

  bool ClimberToggled = false;
};