#include "controlPannel.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

ControlPannel::ControlPannel(Gearbox &ControlPannelMotor, SmartControllerGroup &contGroup) : _ControlPannelMotor(ControlPannelMotor), _contGroup(contGroup) {}



void ControlPannel::TeleopOnUpdate(double dt) {

}

void ControlPannel::AutoOnUpdate(double dt) {

}

void ControlPannel::TestOnUpdate(double dt) {
  
}