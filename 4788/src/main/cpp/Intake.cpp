#include "Intake.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Manual/Teleop Control
IntakeTeleop::IntakeTeleop(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the Intake)
void IntakeTeleop::OnUpdate(double dt) {
  //@TODO auto aim using values from CJ-Vision over nt
}






// Initializes & Defines groups for Auto Control
IntakeAuto::IntakeAuto(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the Intake)
void IntakeAuto::OnUpdate(double dt) {
  //@TODO auto aim during autonomous. (still working on pathweaver)
}
