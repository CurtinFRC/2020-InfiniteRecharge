#include "ControlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(wml::actuators::DoubleSolenoid &ClimberActuator,
														 Gearbox &ControlPannelMotor, 
														 Gearbox &ControlPannelUpMotor, 
														 SmartControllerGroup &contGroup,
														 std::shared_ptr<nt::NetworkTable> &ControlPannelTable) : 
														
														 _ClimberActuator(ClimberActuator),
														 _ControlPannelMotor(ControlPannelMotor), 
														 _ExtendControlPannelMotor(_ExtendControlPannelMotor), 
														 _contGroup(contGroup), 
														 _ControlPannelTable(ControlPannelTable){}
void ControlPannel::TeleopOnUpdate(double dt) {

	if (_contGroup.Get(ControlMap::SpinControlPannelLeft)) {
		ControlPannelPower = 0.5;
	} else if (_contGroup.Get(ControlMap::SpinControlPannelRight)) {
		ControlPannelPower = -0.5;
	} else if (_contGroup.Get(ControlMap::ControlPannelUp)) {
		ControlPannelUpPower = 0.5;
	} else if (_contGroup.Get(ControlMap::ControlPannelDown)) {
		ControlPannelUpPower = -0.5;
	}
	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelPower);
	_ExtendControlPannelMotor.transmission->SetVoltage(12 * ControlPannelUpPower);
}
void ControlPannel::AutoOnUpdate(double dt) {}

void ControlPannel::TestOnUpdate(double dt) {
	double ControlPannelSpeed;
	double ControlPannelUpSpeed;
	double Timeout = 3;

	switch (TestSelector) {
		CringeTimer.Start();
		
		case 1:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelUpSpeed = 0.5;
		} else {
			ControlPannelUpSpeed = 0;
			CringeTimer.Reset();
			TestSelector++;
		}
		break;

		case 2:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelSpeed = 0.5;
		} else {
			ControlPannelSpeed = 0;
			CringeTimer.Reset();
			TestSelector++;
		}
		break;

		case 3:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelSpeed = -0.5;
		} else {
			ControlPannelSpeed = 0;
			CringeTimer.Reset();
			TestSelector++;
		}
		break;

		case 4:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelUpSpeed = -0.5;
		} else {
			ControlPannelUpSpeed = 0;
		}
		break;
		CringeTimer.Stop();
		CringeTimer.Reset();
	}
}