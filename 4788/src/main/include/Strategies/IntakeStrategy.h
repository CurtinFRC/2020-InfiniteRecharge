#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Intake2.h" // Meant to be intake2.h

using ButtonState = wml::controllers::Controller;

class IntakeManualStrategy : wml::Strategy {
 public:
  IntakeManualStrategy(
    Intake &intake,
    wml::controllers::SmartControllerGroup &controllers
    ) : wml::Strategy("Manual"), _intake(intake), _controllers(controllers) {
      Requires(&intake);
      SetCanBeInterrupted(true);
      SetCanBeReused(true);
    }
  void OnUpdate(double dt) override {
    double intake_power;
    if (ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::Intake)))
      intake_power = _controllers.Get(ControlMap::Intake);
    else
      intake_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::Outake));

    // Detect If climber is deployed
    if (_controllers.Get(ControlMap::ClimberToggle, ButtonState::ONRISE)) {
      if (ClimberToggled)
        ClimberToggled = false;
      else
        ClimberToggled = true;
    }

    // Detect if intake is deployed
    if (_controllers.Get(ControlMap::DownIntake, ButtonState::ONRISE)) {
      if (IntakeToggled)
        IntakeToggled = false;
      else 
        IntakeToggled = true;
    }

    // Intake controll, Override if Climber is deployed
    if (!ClimberToggled) {
      if (IntakeToggled) {
        _intake.SetIntake(IntakeState::INTAKING, intake_power);
      } else {
        _intake.SetIntake(IntakeState::STOWED, intake_power);
      }
    } else {
      _intake.SetIntake(IntakeState::DEPLOYED, intake_power);
    }
  }

 private:
  Intake &_intake;
  wml::controllers::SmartControllerGroup &_controllers;

  bool IntakeToggled = false;
  bool ClimberToggled = false;
};