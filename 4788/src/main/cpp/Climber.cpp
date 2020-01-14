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
 /* double UpClimbSpeed;
  double DownClimbSpeed;
  
if (_contGroup.Get(ControlMap::UpClimb)){
double UpClimbSpeed = ControlMap::UpClimb;
ClimberMotor->Set(UpClimbSpeed);

} else{
ClimberMotor->Set(0);
}

if(_contGroup.Get(ControlMap::DownClimb)){
double DownClimbSpeed = ControlMap::DownClimb;
robotMap
ClimberMotor->Set(DownClimbSpeed);
} else{
ClimberMotor->Set(0);
}
*/
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
