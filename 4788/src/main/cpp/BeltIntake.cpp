#include "BeltIntake.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

BeltIntake::BeltIntake(Gearbox &BeltIntakeMotors, actuators::DoubleSolenoid &IntakeDown, SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &BeltIntakeTable) : _BeltIntakeMotors(BeltIntakeMotors), _IntakeDown(IntakeDown),  _contGroup(contGroup), _BeltIntakeTable(BeltIntakeTable) {}

//table = &_pancakes->GetSubTable("Encoder Value");
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
	} else if (_contGroup.Get(ControlMap::Outake)) {
		IntakePower = -1;
	} 
	_BeltIntakeMotors.transmission->SetVoltage(12 * IntakePower);
}

void BeltIntake::AutoOnUpdate(double dt) {}

void BeltIntake::TestOnUpdate(double dt) {

			_BeltIntakeTable->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
	_IntakeDown.SetTarget(wml::actuators::kForward);
  while (_BeltIntakeMotors.encoder->GetEncoderRotations() > 10) {
			_BeltIntakeTable->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
	  double Speed = 1;
		_BeltIntakeMotors.transmission->SetVoltage(12 * Speed);
  } while (_BeltIntakeMotors.encoder->GetEncoderRotations() > 10) {
			_BeltIntakeTable->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
		double Speed = -1;
		_BeltIntakeMotors.transmission->SetVoltage(12 * Speed);
	}
			_BeltIntakeTable->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
	_IntakeDown.SetTarget(wml::actuators::kReverse);
}
