#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, sensors::LimitSwitch &StartMag, sensors::LimitSwitch &Position1, sensors::LimitSwitch &Position5, SmartControllerGroup &contGroup) : _MagazineMotors(MagazineMotors), _StartMag(StartMag), _Position1(Position1), _Position5(Position5), _contGroup(contGroup) {}

void MagLoader::TeleopOnUpdate(double dt) {

}

void MagLoader::AutoOnUpdate(double dt) {

}

void MagLoader::TestOnUpdate(double dt) {
  
}