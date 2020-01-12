#include "Turret.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

RobotMap::ControlSystem controlSystem;

// Initializes & Defines groups for Manual/Teleop Control
TurretTeleop::TurretTeleop(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the turret)
void TurretTeleop::OnUpdate(double dt) {
  //@TODO auto aim using values from CJ-Vision over nt
}






// Initializes & Defines groups for Auto Control
TurretAuto::TurretAuto(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the turret)
void TurretAuto::OnUpdate(double dt) {
  //@TODO auto aim during autonomous. (still working on pathweaver)
}







TurretTest::TurretTest(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

void TurretTest::OnUpdate(double dt) {
  //@TODO zero encoders activate motors and if it's getting vision tracking values. Basically... a test. lol
}