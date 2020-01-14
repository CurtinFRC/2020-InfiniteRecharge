#include "Intake.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

RobotMap robotMap;

// Initializes & Defines groups for Manual/Teleop Control
IntakeTeleop::IntakeTeleop(std::string name, SmartControllerGroup &contGroup) : Strategy(name), _contGroup(contGroup) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);

}

// On Loop Update, this code runs (Just the Intake)
void IntakeTeleop::OnUpdate(double dt) {
  double InSpeed;
  if (_contGroup.Get(ControlMap::IntakeIn) > ControlMap::triggerDeadzone) {
    InSpeed = 1;
  } else {
    InSpeed = 0;
  }

  robotMap.intake.LintakeMotor.Set(InSpeed);
  robotMap.intake.RintakeMotor.Set(InSpeed);
  robotMap.intake.MintakeMotor.Set(InSpeed);

  double OutSpeed;
  if(_contGroup.Get(ControlMap::IntakeOut) > ControlMap::triggerDeadzone){
    OutSpeed = -0.7;
  } else {
    OutSpeed = 0;
  }
  robotMap.intake.LintakeMotor.Set(OutSpeed);
  robotMap.intake.RintakeMotor.Set(OutSpeed);
  robotMap.intake.MintakeMotor.Set(OutSpeed);
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
