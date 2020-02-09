#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, 
                     frc::AnalogInput &StartMag, 
                     frc::AnalogInput &Position1, 
                     frc::AnalogInput &Position5, 
                     SmartControllerGroup &contGroup) : 
                     
                     _MagazineMotors(MagazineMotors), 
                     _StartMag(StartMag), 
                     _Position1(Position1), 
                     _Position5(Position5), 
                     _contGroup(contGroup) {}

void MagLoader::TeleopOnUpdate(double dt) {
  double MagazinePower;

  // Shifting Mag up
  if (_contGroup.Get(ControlMap::ShiftUpMagazine)) {
    if (MagOverride) {
      MagazinePower = 1;
    } else {
      if (_Position5.GetAverageValue() < ControlMap::MagazineBallThresh) {
        MagazinePower = 0;
      } else {
        MagazinePower = 1;
      }
    }
  // Shifting Mag Down
  } else if (_contGroup.Get(ControlMap::ShiftDownMagazine)) {
    if (MagOverride) {
      MagazinePower = -1;
    } else {
      if (_Position5.GetAverageValue() < ControlMap::MagazineBallThresh) {
        MagazinePower = 0;
      } else {
        MagazinePower = -1;
      }
    }
  }

  // Fire Control
  if (_contGroup.Get(ControlMap::TurretFire)) {
    MagazinePower = 1;
  }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}
void MagLoader::AutoOnUpdate(double dt) {

  // Auto Control
  // if (_Position5.Get() >= 1) {
  //   MagazinePower = 0;
  // } else if (_Position1.Get() >= 1) {
  //   MagazinePower = 0;
  // } else if (_StartMag.Get() >= 1) {
  //   MagazinePower = 1;
  // }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}

void MagLoader::TestOnUpdate(double dt) {

  if (!LimitTest) {
    if (magtest) {
      std::cout << "Magazine Test Succesful" << std::endl;
      magtest = false;
    }
  } else {
    // Forward Test
    if (FwdTest) {
      if (_MagazineMotors.encoder->GetEncoderRotations() < ControlMap::MagTestCaseRotations) {
        MagazinePower = 0.5;
      } else {
        MagazinePower = 0;
        FwdTest = false;
      }
    }
    // Backward Test
    if (!FwdTest) {
      if (_MagazineMotors.encoder->GetEncoderRotations() > 0) {
        MagazinePower = -1;
      } else {
        MagazinePower = 0;
        BckwdTest = false;
      }
    }

    // Limit Test
    if (!BckwdTest) {

    }
  }

  _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
}