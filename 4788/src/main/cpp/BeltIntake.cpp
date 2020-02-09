#include "BeltIntake.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

BeltIntake::BeltIntake(Gearbox &BeltIntakeMotors, 
											 actuators::DoubleSolenoid &IntakeDown, 
											 SmartControllerGroup &contGroup) : 
											 
											 _BeltIntakeMotors(BeltIntakeMotors), 
											 _IntakeDown(IntakeDown),  
											 _contGroup(contGroup){}

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
		IntakePower = _contGroup.Get(ControlMap::Intake);
	} else if (_contGroup.Get(ControlMap::Outake)) {
		IntakePower = -_contGroup.Get(ControlMap::Outake);
	} 
	_BeltIntakeMotors.transmission->SetVoltage(12 * IntakePower);
}

void BeltIntake::AutoOnUpdate(double dt) {}

void BeltIntake::TestOnUpdate(double dt) {

	//_pancakes->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
	_IntakeDown.SetTarget(wml::actuators::kForward);
  while (_BeltIntakeMotors.encoder->GetEncoderRotations() > 10) {
	//	table2->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
	  double Speed = 1;
		_BeltIntakeMotors.transmission->SetVoltage(12 * Speed);
  } while (_BeltIntakeMotors.encoder->GetEncoderRotations() > 10) {
	//	table2->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
		double Speed = -1;
		_BeltIntakeMotors.transmission->SetVoltage(12 * Speed);
	}
	//	table2->PutNumber("Belt Intake encoder value ", _BeltIntakeMotors.encoder->GetEncoderRotations());
	_IntakeDown.SetTarget(wml::actuators::kReverse);
}
