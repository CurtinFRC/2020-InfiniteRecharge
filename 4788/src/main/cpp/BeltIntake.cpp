#include "BeltIntake.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

BeltIntake::BeltIntake(Gearbox &BeltIntakeMotors, SmartControllerGroup &contGroup) : _BeltIntakeMotors(BeltIntakeMotors), _contGroup(contGroup) {}

void BeltIntake::TeleopOnUpdate(double dt) {

	double IntakePower;

if (_contGroup.Get(ControlMap::Intake)) {
  IntakePower = 1;
} else {}

if (_contGroup.Get(ControlMap::Outake)) {
	IntakePower = -1;
} else {}

_BeltIntakeMotors.transmission->SetVoltage(12 * IntakePower);
}

void BeltIntake::AutoOnUpdate(double dt) {

}

void BeltIntake::TestOnUpdate(double dt) {
  
}