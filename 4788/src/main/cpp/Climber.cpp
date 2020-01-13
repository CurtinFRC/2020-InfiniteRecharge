#include "Climber.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Manual/Teleop Control
ClimberTeleop::ClimberTeleop(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the Climber)
void ClimberTeleop::OnUpdate(double dt) {
  //@TODO auto aim using values from CJ-Vision over nt
}






// Initializes & Defines groups for Auto Control
ClimberAuto::ClimberAuto(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the Climber)
void ClimberAuto::OnUpdate(double dt) {
  //@TODO auto aim during autonomous. (still working on pathweaver)
}
