#pragma once

#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "Intake.h"

using ButtonState = wml::controllers::Controller;

class IntakeManualStrategy : public wml::Strategy {
 public:
  IntakeManualStrategy(
    Intake &intake,
    wml::controllers::SmartControllerGroup &controllers
    ) : _intake(intake), _controllers(controllers) {
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
        _intake.SetIntake(IntakeState::DEPLOYED, intake_power);
      } else {
        _intake.SetIntake(IntakeState::STOWED, 0);
      }
    } else {
      _intake.SetIntake(IntakeState::DEPLOYED, 0);
    }
  }

 private:
  Intake &_intake;
  wml::controllers::SmartControllerGroup &_controllers;

  bool IntakeToggled = false;
  bool ClimberToggled = false;
};