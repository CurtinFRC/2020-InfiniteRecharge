#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, sensors::LimitSwitch &StartMag, sensors::LimitSwitch &Position1, sensors::LimitSwitch &Position5, SmartControllerGroup &contGroup) : _MagazineMotors(MagazineMotors), _StartMag(StartMag), _Position1(Position1), _Position5(Position5), _contGroup(contGroup) {}

void MagLoader::TeleopOnUpdate(double dt) {
  double MagazinePower;

  // Auto Control
  if (_Position5.Get() >= 1) {
    MagazinePower = 0;
  } else if (_Position1.Get() >= 1) {
    MagazinePower = 0;
  } else if (_StartMag.Get() >= 1) {
    MagazinePower = 1;
  }
  
  // Manual Control
  else if (_contGroup.Get(ControlMap::ShiftUpMagazine)) {
    MagazinePower = 1;
  } else if (_contGroup.Get(ControlMap::ShiftDownMagazine)) {
    MagazinePower = -1;
  }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}

void MagLoader::AutoOnUpdate(double dt) {
  double MagazinePower;


  // Auto Control
  if (_Position5.Get() >= 1) {
    MagazinePower = 0;
  } else if (_Position1.Get() >= 1) {
    MagazinePower = 0;
  } else if (_StartMag.Get() >= 1) {
    MagazinePower = 1;
  }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}

void MagLoader::TestOnUpdate(double dt) {
  double MagazinePower;
  
  for (int i = 0; i > 1000; i++) {
    MagazinePower = 1;
    _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
  } 
  for (int i = 0; i > 1000; i++) {
    MagazinePower = -1;
    _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
  }
}