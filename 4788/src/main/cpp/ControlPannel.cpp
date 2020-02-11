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
														 _ControlPannelUpMotor(ControlPannelUpMotor), 
														 _contGroup(contGroup), 
														 _ControlPannelTable(ControlPannelTable){}
void ControlPannel::TeleopOnUpdate(double dt) {

	if (_contGroup.Get(ControlMap::SpinControlPannelLeft)) {
		ControlPannelPower = 0.5; // <- Anna... magic numbers go in ControlMap
	} else if (_contGroup.Get(ControlMap::SpinControlPannelRight)) {
		ControlPannelPower = -0.5;
	} else if (_contGroup.Get(ControlMap::ControlPannelUp)) {
		ControlPannelUpPower = 0.5;
	} else if (_contGroup.Get(ControlMap::ControlPannelDown)) {
		ControlPannelUpPower = -0.5;
	}
	_ControlPannelMotor.transmission->SetVoltage(12 * ControlPannelPower);
	_ControlPannelUpMotor.transmission->SetVoltage(12 * ControlPannelUpPower);
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
	

}