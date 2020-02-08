#include "ControlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(Gearbox &ControlPannelMotor, wml::actuators::DoubleSolenoid &ControlPannelUpSol, SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &ControlPannelTable) : _ControlPannelMotor(ControlPannelMotor), _ControlPannelUpSol(ControlPannelUpSol), _contGroup(contGroup), _ControlPannelTable(ControlPannelTable) {}
void ControlPannel::TeleopOnUpdate(double dt) {
	double ControlPannelPower;
	double ControlPannelUpPower;
	
	if (_contGroup.Get(ControlMap::SpinControlPannelLeft)) {
		ControlPannelPower = 0.5;
	} else if (_contGroup.Get(ControlMap::SpinControlPannelRight)) {
		ControlPannelPower = -0.5;
	} else if (_contGroup.Get(ControlMap::ControlPannelUp)) {
	
	} else if (_contGroup.Get(ControlMap::ControlPannelDown)) {
		ControlPannelUpPower = -0.5;
	}
	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelPower);
	//_ControlPannelUpSol.transmission->SetVoltage(12 * ControlPannelUpPower);
}
void ControlPannel::AutoOnUpdate(double dt) {}

void ControlPannel::TestOnUpdate(double dt) {
	// double ControlPannelPower;
	// double ControlPannelUpPower;

	

	// timer.Start();
	// while (timer.Get() <= 10) {
	// 	double ControlPannelSpeed = 1;
	// 	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelSpeed);
	// } while (timer.Get() <= 20) {
	// 	double ControlPannelSpeed = -1;
	// 	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelSpeed);
	// }

//do after climber 
}