#pragma once

#include "strategy/Strategy.h"
#include "TurretStrategy.h"
#include "MagLoaderStrategy.h"
#include "IntakeStrategy.h"
#include "ClimberStrategy.h"

class StrategyCaller : wml::StrategyBuilder {
 public:

  void OnUpdate(double dt) override {

  }


 private:
  Turret &_turret;
  MagLoader &_magLoader;
  Intake &_intake;
};

