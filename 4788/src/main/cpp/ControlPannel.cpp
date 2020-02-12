#include "ControlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(wml::actuators::DoubleSolenoid &ClimberActuator,
														 Gearbox &ControlPannelMotor, 
														 wml::actuators::DoubleSolenoid &ControlPannelUpSol, 
														 SmartControllerGroup &contGroup,
														 std::shared_ptr<nt::NetworkTable> &ControlPannelTable) : 
														
														 _ClimberActuator(ClimberActuator),
														 _ControlPannelMotor(ControlPannelMotor), 
														 _ControlPannelUpSol(ControlPannelUpSol), 
														 _contGroup(contGroup), 
														 _ControlPannelTable(ControlPannelTable){}
void ControlPannel::TeleopOnUpdate(double dt) {
	double ControlPannelPower;
	
	if (_contGroup.Get(ControlMap::SpinControlPannelLeft)) {
		ControlPannelPower = 0.5;
	} else if (_contGroup.Get(ControlMap::SpinControlPannelRight)) {
		ControlPannelPower = -0.5;
	} else if (_contGroup.Get(ControlMap::ControlPannelUp)) {
		_ControlPannelUpSol.SetTarget(wml::actuators::kForward);
	} else if (_contGroup.Get(ControlMap::ControlPannelDown)) {
		_ControlPannelUpSol.SetTarget(wml::actuators::kReverse);
	}
	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelPower);
}
void ControlPannel::AutoOnUpdate(double dt) {}

void ControlPannel::TestOnUpdate(double dt) {

//if the ControlPannel Mechanism is on the turret 
	/*double ControlPannelSpeed;
	_ClimberActuator.SetTarget(wml::actuators::kForward);

	CringeTimer.Start();
	while (CringeTimer.Get() <= 5) {
		ControlPannelSpeed = 0.5;
	} while (CringeTimer.Get() <= 10) {
		ControlPannelSpeed = -0.5;
	}
	CringeTimer.Stop();
	CringeTimer.Reset();
	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelSpeed);
	_ClimberActuator.SetTarget(wml::actuators::kReverse);*/

//if it is in a random space 


//only have 1 uncommeted 

	double ControlPannelSpeed;

	CringeTimer.Start();
	if (CringeTimer.Get() <= 5) {
		ControlPannelSpeed = 0.5;
	} else {
		ControlPannelSpeed = 0;
	}
	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelSpeed);
	CringeTimer.Stop();
	CringeTimer.Reset();

}