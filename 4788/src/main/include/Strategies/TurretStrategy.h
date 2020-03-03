#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

#include "ControlMap.h"
#include "Turret.h" // meant to be turret2.h

class TurretDriverControl : wml::Strategy {
 public:
  TurretDriverControl(
    const Turret &turret,
    const wml::controllers::SmartControllerGroup &controllers,
  ) : wml::Strategy("Driver"), _turret(turret), _controllers(controllers) {
    Requires(&turret);
    SetCanBeInterrupted(true);
    SetCanBeReused(true);
  }



  void OnUpdate(double dt) override {
    double angular_power = ControlMap::doJoyDeadzone(-_controllers.Get(ControlMap::TurretManualAngle));
    double rotational_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::TurretManualRotate));
    rotational_power *= std::fabs(rotational_power);
    double flywheel_power = _controllers.Get(ControlMap::TurretFlyWheelSpinUp);

    if (_controllers.Get(/* A BUTTON */))
      turret.SetRotation(TurretRotationState::PID, Vision.getDesiredRotation());
    else
      turret.SetRotation(TurretRotationState::MANUAL, rotational_power);
    turret.SetFlywheel(TurretFlywheelState::MANUAL, flywheel_power);
  }



 private:
  const Turret &_turret;
  const wml::controllers::SmartControllerGroup &_controllers;
};

