#include "ControlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(Gearbox &ControlPannelMotor, 
														 Gearbox &ExtendControlPannelMotor, 
														 SmartControllerGroup &contGroup,
														 std::shared_ptr<nt::NetworkTable> &ControlPannelTable) : 
							
														 _ControlPannelMotor(ControlPannelMotor), 
														 _ExtendControlPannelMotor(ExtendControlPannelMotor), 
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
	double Timeout = 3;
	CringeTimer.Start();

	switch (TestSelector) {
	
		case 1:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelUpPower = 0.5;
		} else {
			ControlPannelUpPower = 0;
			CringeTimer.Reset();
			TestSelector++;
		}
		break;

		case 2:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelPower = 0.5;
		} else {
			ControlPannelPower = 0;
			CringeTimer.Reset();
			TestSelector++;
		}
		break;

		case 3:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelPower = -0.5;
		} else {
			ControlPannelPower = 0;
			CringeTimer.Reset();
			TestSelector++;
		}
		break;

		case 4:
		if (CringeTimer.Get() <= Timeout) {
			ControlPannelUpPower = -0.5;
		} else {
			ControlPannelUpPower = 0;
		}
		break;
		CringeTimer.Stop();
		CringeTimer.Reset();
	}
}