#include "ControlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(Gearbox &ControlPannelMotor, actuators::DoubleSolenoid &PannelPnSol, SmartControllerGroup &contGroup) : _ControlPannelMotor(ControlPannelMotor), _PannelPnSol(PannelPnSol), _contGroup(contGroup) {}



void ControlPannel::TeleopOnUpdate(double dt) {



}

void ControlPannel::AutoOnUpdate(double dt) {
//not used 
}

void ControlPannel::TestOnUpdate(double dt) {
// 
}