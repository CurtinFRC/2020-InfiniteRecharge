#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Intake.h"
#include "Climber.h"

using ButtonState = wml::controllers::Controller;

class IntakeManualStrategy : public wml::Strategy {
 public:
  IntakeManualStrategy(
    Intake &intake,
    Climber &climber,
    wml::controllers::SmartControllerGroup &controllers
    ) : _intake(intake), 
        _controllers(controllers),
        _climber(climber) {
      Requires(&intake);
      SetCanBeInterrupted(true);
      SetCanBeReused(true);
    }
  void OnUpdate(double dt) override {
    double intake_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::Intake));
    double outtake_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::Outake));
    
    if (_climber.GetClimberState() != ClimberState::DOWN) {
      _intake.SetIntake(IntakeState::DEPLOYED, 0);
    } else {
      // Detect if intake is deployed
      if (_controllers.Get(ControlMap::DownIntake, ButtonState::ONRISE))
        IntakeToggled = !IntakeToggled;

      if (IntakeToggled)
        _intake.SetIntake(IntakeState::DEPLOYED, intake_power - outtake_power);
      else
        _intake.SetIntake(IntakeState::STOWED, 0);
    }
  }

 private:
  Intake &_intake;
  wml::controllers::SmartControllerGroup &_controllers;
  Climber &_climber;

  bool IntakeToggled = false;
};