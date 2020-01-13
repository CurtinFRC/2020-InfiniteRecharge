#include "MagLoader.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Manual/Teleop Control
MagLoaderTeleop::MagLoaderTeleop(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the MagLoader)
void MagLoaderTeleop::OnUpdate(double dt) {
  //@TODO auto aim using values from CJ-Vision over nt
}






// Initializes & Defines groups for Auto Control
MagLoaderAuto::MagLoaderAuto(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the MagLoader)
void MagLoaderAuto::OnUpdate(double dt) {
  //@TODO auto aim during autonomous. (still working on pathweaver)
}



// Initializes & Defines groups for Auto Control
MagLoaderTest::MagLoaderTest(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the MagLoader)
void MagLoaderTest::OnUpdate(double dt) {
  //@TODO
}