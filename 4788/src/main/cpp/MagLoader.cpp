#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, sensors::LimitSwitch &StartMag, sensors::LimitSwitch &Position1, sensors::LimitSwitch &Position5, SmartControllerGroup &contGroup) : _MagazineMotors(MagazineMotors), _StartMag(StartMag), _Position1(Position1), _Position5(Position5), _contGroup(contGroup) {}

void MagLoader::TeleopOnUpdate(double dt) {
  double MagazinePower;


  // Automated Mag Block
  if (_Position5.Get()) {
    MagazinePower = 0;
  } else if (_contGroup.Get(ControlMap::ShiftUpMagazine)) {
    MagazinePower = 1;
  } else if (_contGroup.Get(ControlMap::ShiftDownMagazine)) {
    MagazinePower = -1;
  }else {
    if (_StartMag.Get()) {
      MagazinePower = 1;
    } 
    if (_Position1.Get()) {
      MagazinePower = 0;
    }
  } 

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}

void MagLoader::AutoOnUpdate(double dt) {
  double MagazinePower;


  // Automated Mag Block
  if (_Position5.Get()) {
    MagazinePower = 0;
  } else if (_contGroup.Get(ControlMap::ShiftUpMagazine)) {
    MagazinePower = 1;
  } else if (_contGroup.Get(ControlMap::ShiftDownMagazine)) {
    MagazinePower = -1;
  }else {
    if (_StartMag.Get()) {
      MagazinePower = 1;
    } 
    if (_Position1.Get()) {
      MagazinePower = 0;
    }
  } 

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}

void MagLoader::TestOnUpdate(double dt) {
  double MagazinePower;
  
  MagazinePower = 1;
  
  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}