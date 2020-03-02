#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Climber.h"

class CimberManualStrategy : wml::Strategy {
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
    double leftClimber_power = ControlMap::doJoydeadzone(-_controllers.Get(ControlMap::ClimberControlLeft));
    double rightClimber_power = Controlmap::doJoydeadzone(-_controllers.Get(ControlMap::ClimberControlRight));

    if (_controllers.Get(ControlMap::ClimberToggle)) {
      
    }
  }
 private:
  const Climber &_climber;
  const wml::controllers::SmartControllerGroup &_controllers;
}