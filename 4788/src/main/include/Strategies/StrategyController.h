#pragma once

#include "RobotMap.h"
#include "strategy/Strategy.h"
#include "TurretStrategy.h"
#include "MagLoaderStrategy.h"
#include "IntakeStrategy.h"
#include "ClimberStrategy.h"

class ManualStrategyController : wml::StrategyBuilder {
 public:
  ManualStrategyController(
    const TurretManualStrategy &turret,
    const MagLoaderManualStrategy &magLoader,
    const ClimberManualStrategy &climber,
    const IntakeManualStrategy &intake,
    const RobotMap &robotMap,
    const wml::controlers::SmartControllerGroup &controllers
  ) : wml::Strategy("Manual"), 
    _turret(turret), _magLoader(magLoader), _climber(climber), _intake(intake), _robotMap(robotMap), _controllers(controllers) {}


  void OnUpdate(double dt) override {
    StrategyBuilder builder;
    builder.Start();
    builder.Add(std::make_shared<TurretManualStrategy>(_turret, _controllers));
    builder.Add(std::make_shared<MagLoaderManualStrategy>(_magLoader, _controllers));
    builder.Add(std::make_shared<ClimberManualStrategy>(_climber, _controllers));
    builder.Add(std::Make_shared<IntakeManualStrategy>(_intake, _controllers));
    Schedule(builder.Build());
  }

 private:
  Turret &_turret;
  MagLoader &_magLoader;
  Climber &_climber;
  Intake &_intake;
  RobotMap &_robotMap;
  wml::controllers::SmartControllerGroup &_controllers;
};


class AutoStrategyController : wml::StrategyBuilder {

}

