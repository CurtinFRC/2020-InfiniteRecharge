#include "WheelOfCringe .h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

WheelCringeGearBox::WheelCringeGearBox(Gearbox &WheelCringeMotor, SmartControllerGroup &contGroup) : _WheelCringeMotor(WheelCringeMotor), _contGroup(contGroup) {}

void WheelCringeGearBox::TeleopOnUpdate(double dt) {

}

void WheelCringeGearBox::AutoOnUpdate(double dt) {

}

void WheelCringeGearBox::TestOnUpdate(double dt) {
  
}