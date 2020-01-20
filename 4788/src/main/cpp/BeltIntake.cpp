#include "BeltIntake.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

BeltIntake::BeltIntake(Gearbox &BeltIntakeMotors, SmartControllerGroup &contGroup) : _BeltIntakeMotors(BeltIntakeMotors), _contGroup(contGroup) {}

void BeltIntake::TeleopOnUpdate(double dt) {

}

void BeltIntake::AutoOnUpdate(double dt) {

}

void BeltIntake::TestOnUpdate(double dt) {
  
}