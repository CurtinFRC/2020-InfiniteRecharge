#include "BeltIntake.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

BeltIntake::BeltIntake(Gearbox &BeltIntakeMotors, 
											 actuators::DoubleSolenoid &IntakeDown, 
											 SmartControllerGroup &contGroup,
											 int &autoSelector,
											 bool &StartDoComplete,
											 bool &strt,
											 bool &p1,
											 bool &p2,
											 bool &p3,
											 bool &end) : 
											 
											 _BeltIntakeMotors(BeltIntakeMotors), 
											 _IntakeDown(IntakeDown),  
											 _contGroup(contGroup),
											 _autoSelector(autoSelector),
											 _StartDoComplete(StartDoComplete),
											 _strt(strt),
											 _p1(p1),
											 _p2(p2),
											 _p3(p3),
											 _end(end) {
	_IntakeDown.SetTarget(wml::actuators::BinaryActuatorState::kForward); // Default State
}

void BeltIntake::TeleopOnUpdate(double dt) {


	if (_contGroup.Get(ControlMap::DownIntake, Controller::ONRISE)) {
		if (ToggleEnabled) {
			_IntakeDown.SetTarget(wml::actuators::kForward);
			ToggleEnabled = false;
		} else if (!ToggleEnabled) {
			_IntakeDown.SetTarget(wml::actuators::kReverse);
			ToggleEnabled = true;
		}
	} 
	

	IntakePower = _contGroup.Get(ControlMap::Intake) > ControlMap::triggerDeadzone ? _contGroup.Get(ControlMap::Intake) :
	_contGroup.Get(ControlMap::Outake) > ControlMap::triggerDeadzone ? -_contGroup.Get(ControlMap::Outake) : 0;

	_IntakeDown.Update(dt);
	_BeltIntakeMotors.transmission->SetVoltage(12 * IntakePower);
}

void BeltIntake::AutoOnUpdate(double dt) {

	switch (IntakeStop) {
		case 1:
			switch (_autoSelector) {
				case 1: // 8 ball auto, intake 5 balls
					if (_p1) {
						//solenoid down then set the motor spinning
						_IntakeDown.SetTarget(wml::actuators::kForward);
						IntakePower = 0.7;
					} else if (!_p1){
						//solenoid up and motor off
						_IntakeDown.SetTarget(wml::actuators::kReverse);
						IntakePower = 0;
					}
					_BeltIntakeMotors.transmission->SetVoltage(12 * IntakePower);
				break;

				case 2: // 6 ball auto 
					if (_p1) {
						//solenoid down then set the motor spinning 
						_IntakeDown.SetTarget(wml::actuators::kForward);
						IntakePower = 0.7;
					} else if (!_p1) {
						//solenoid up and motor off
						_IntakeDown.SetTarget(wml::actuators::kReverse);
						IntakePower = 0;
					}
				break;
			}

		break;
	}
}

void BeltIntake::TestOnUpdate(double dt) {

	timer.Start();

	switch (TestType) {
		case 1: // forwards
			if (timer.Get() < timeout) {
				_IntakeDown.SetTarget(wml::actuators::kForward);
				IntakePower = 1;
			} else {
				IntakePower = 0;
				TestType++;
				timer.Reset();
			}
		break;

		case 2:
			if (timer.Get() < timeout) {
				IntakePower = -1;
			} else {
				timer.Reset();
				TestType++;
				_IntakeDown.SetTarget(wml::actuators::kReverse);
			}
		break;
	}
	_BeltIntakeMotors.transmission->SetVoltage(12 * IntakePower);
	_IntakeDown.Update(dt);
}

