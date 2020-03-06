#pragma once

#include "strategy/Strategy.h"
#include "strategy/StrategyBuilder.h"
#include "strategy/StrategyController.h"

// Strategy files
#include "Strategies/TurretStrategy.h"
#include "Strategies/IntakeStrategy.h"
#include "Strategies/MagLoaderStrategy.h"
#include "DriveSystem.h"

wml::StrategyBuilder builder;

class AutoController {
 public:
  AutoController(
    Turret &turret,
    Intake &intake,
    MagLoader &magLoader,
    wml::Drivetrain &drivetrain,
    WayFinder &wayFinder,
    RobotMap &robotMap
  ) : _turret(turret), 
      _intake(intake), 
      _magLoader(magLoader), 
      _drivetrain(drivetrain),
      _wayFinder(wayFinder),
      _robotMap(robotMap) {
    _wayFinder.AutoConfig(ControlMap::MaxAutoDrivetrainSpeed, ControlMap::MaxAutoTurnSpeed);
  }


  void Update(double dt) {
    builder.Start();
    builder.Add(std::make_shared<DrivetrainAuto>(_drivetrain, _robotMap.driveSystem.ChangeGearing, _robotMap.driveSystem.Shift2PTO, _wayFinder, WayFinder::Waypoint{3.2, -2.4, -30, 5.4, -0.7, 30, false}));

  }

 private:
  Turret &_turret;
  Intake &_intake;
  MagLoader &_magLoader;
  wml::Drivetrain &_drivetrain;
  WayFinder &_wayFinder;
  RobotMap &_robotMap;

  frc::Timer timer;
};