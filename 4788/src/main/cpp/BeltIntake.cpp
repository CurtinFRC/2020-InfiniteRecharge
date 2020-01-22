#include "BeltIntake.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

BeltIntake::BeltIntake(Gearbox &BeltIntakeMotors, actuators::DoubleSolenoid &IntakeDown, SmartControllerGroup &contGroup) : _BeltIntakeMotors(BeltIntakeMotors), _IntakeDown(IntakeDown), _contGroup(contGroup) {}

void BeltIntake::TeleopOnUpdate(double dt) {

double IntakePower;


if (_contGroup.Get(ControlMap::DownIntake, Controller::ONFALL)) {
	if (ToggleEnabled) {
		_IntakeDown.SetTarget(wml::actuators::kForward);
		ToggleEnabled = false;
	} else if (!ToggleEnabled) {
		_IntakeDown.SetTarget(wml::actuators::kReverse);
		ToggleEnabled = true;
	}
}

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
  timer.Start();
  while (timer.Get() >= 10) {
	  double Speed = 1;
		_BeltIntakeMotors.transmission->SetVoltage(12 * Speed);
  }
  timer.Stop();
  timer.Reset();
	timer.Start();
	while (timer.Get() >= 10) {
		double Speed = -1;
		_BeltIntakeMotors.transmission->SetVoltage(12 * Speed);
	}
	timer.Stop();
	timer.Reset();
  
}