#include "ControlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(Gearbox &ControlPannelMotor, actuators::DoubleSolenoid &PannelPnSol, SmartControllerGroup &contGroup) : _ControlPannelMotor(ControlPannelMotor), _PannelPnSol(PannelPnSol), _contGroup(contGroup) {}

void ControlPannel::TeleopOnUpdate(double dt) {

	double ControlPannelPower;

	if (_contGroup.Get(ControlMap::ControlPannelUp)) {
		_PannelPnSol.SetTarget(wml::actuators::kForward);
	} else {}
	
	if (_contGroup.Get(ControlMap::ControlPannelDown)) {
		_PannelPnSol.SetTarget(wml::actuators::kReverse);
	} else {}

	if (_contGroup.Get(ControlMap::SpinControlPannelLeft)) {
		ControlPannelPower = 0.5;
	} else {}

	if (_contGroup.Get(ControlMap::SpinControlPannelRight)) {
		ControlPannelPower = -0.5;
	} else {}

	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelPower);
}
void ControlPannel::AutoOnUpdate(double dt) {
//not used 
}

void ControlPannel::TestOnUpdate(double dt) {



}