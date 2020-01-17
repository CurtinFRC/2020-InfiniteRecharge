#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, SmartControllerGroup &contGroup) : _MagazineMotors(MagazineMotors), _contGroup(contGroup) {}

void MagLoader::TeleopOnUpdate(double dt) {

}

void MagLoader::AutoOnUpdate(double dt) {

}

void MagLoader::TestOnUpdate(double dt) {
  
}