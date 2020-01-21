#include "Climber.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(actuators::DoubleSolenoid &ClimberActuator, SmartControllerGroup &contGroup) : _ClimberActuator(ClimberActuator), _contGroup(contGroup) {}

void Climber::TeleopOnUpdate(double dt) {

//if (_contGroup.Get(ControlMap::))
}
void Climber::AutoOnUpdate(double dt) {

}

void Climber::TestOnUpdate(double dt) {
  
}

