#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, 
                     frc::AnalogInput &StartMag, 
                     frc::AnalogInput &Position1, 
                     frc::AnalogInput &Position5, 
                     SmartControllerGroup &contGroup): 
                     
                     _MagazineMotors(MagazineMotors), 
                     _StartMag(StartMag), 
                     _Position1(Position1), 
                     _Position5(Position5), 
                     _contGroup(contGroup) {
  // _StartMag.SetAverageBits(1);
  // _Position1.SetAverageBits(1);
  // _Position5.SetAverageBits(1);
}


void MagLoader::AutoMag() {

  // Auto Control
  if (_Position5.GetAverageValue() >= ControlMap::MagazineBallThreshFinal) {
    MagazinePower = 0;
  } else if (_Position1.GetAverageValue() >= ControlMap::MagazineBallThreshIndex) {
    MagazinePower = 0;
  } else if (_StartMag.GetAverageValue() >= ControlMap::MagazineBallThreshStart) {
    MagazinePower = 0.7;
  } else {
    MagazinePower = 0;
  }
}

void MagLoader::TeleopOnUpdate(double dt) {

  // mag override from auto to manual
  if (_contGroup.Get(ControlMap::ManualMag, Controller::ONRISE)) {
    if (MagOverride) {
      MagOverride = false;
    } else {
      MagOverride = true;
    }
  }

  // Shifting Mag up
  if (_contGroup.Get(ControlMap::ShiftUpMagazine)) {
    if (MagOverride) {
      MagazinePower = 1;
    } else {
      if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThreshFinal) {
        MagazinePower = 0;
      } else {
        MagazinePower = 0.7;
      }
    }
  // Shifting Mag Down
  } else if (_contGroup.Get(ControlMap::ShiftDownMagazine)) {
    if (MagOverride) {
      MagazinePower = -0.7;
    } else {
      if (_Position5.GetAverageValue() < ControlMap::MagazineBallThreshFinal) {
        MagazinePower = 0;
      } else {
        MagazinePower = -0.7;
      }
    }
  } else {
    MagazinePower = 0;
  }

  
  if (!MagOverride) {
    AutoMag();
  }


  // Fire Control (Doesn't care about sensors or override)
  if (_contGroup.Get(ControlMap::TurretFire)) {
    MagazinePower = 1;
  }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}
void MagLoader::AutoOnUpdate(double dt) {
  AutoMag();
 // _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}

void MagLoader::TestOnUpdate(double dt) {

  //@TODO add more test cases when you know what the  will do
  switch (testType) {
    case 1:
      if (_MagazineMotors.encoder->GetEncoderRotations() < ControlMap::MagTestCaseRotations) {
        MagazinePower = 1;
      } else {
        MagazinePower = 0;
        testType++;
      }
    break;
  }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}