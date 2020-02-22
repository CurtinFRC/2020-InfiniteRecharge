#include "MagLoader.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

MagLoader::MagLoader(Gearbox &MagazineMotors, 
                     frc::AnalogInput &StartMag, 
                     frc::AnalogInput &Position1, 
                     frc::AnalogInput &Position5, 
                     SmartControllerGroup &contGroup,
                     int &autoSelector,
                     bool &StartDoComplete,
                     bool &strt,
                     bool &p1,
                     bool &p2,
                     bool &p3,
                     bool &end): 
                     
                     _MagazineMotors(MagazineMotors), 
                     _StartMag(StartMag), 
                     _Position1(Position1), 
                     _Position5(Position5), 
                     _contGroup(contGroup),
                     _autoSelector(autoSelector),
                     _StartDoComplete(StartDoComplete),
                     _strt(strt),
                     _p1(p1),
                     _p2(p2),
                     _p3(p3),
                     _end(end) {}


void MagLoader::AutoMag() {

  // Auto Control
  if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThresh) {
    MagazinePower = 0;
  } else if (_Position1.GetAverageValue() <= ControlMap::MagazineBallThresh) {
    MagazinePower = 0;
  } else if (_StartMag.GetAverageValue() <= ControlMap::MagazineBallThresh) {
    MagazinePower = 0.7;
  }

  switch (MagStop) {
    case 1:
    switch (_autoSelector) {
      case 1: // 8 ball auto 3 then 5
        if (_p3) { // shoot 3 balls, the flywheel has already spun up
          if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThresh) {
            MagazinePower = 0.7;
            _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
          } else {
            _MagazineMotors.transmission->SetVoltage(0);
            _p1 = false;
          }
        }

        if (_end) { // shoot 5 balls, the flywheel has already spun up
          if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThresh)
          MagazinePower = 0.7;
          _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
        } else {
          _MagazineMotors.transmission->SetVoltage(0);
          _p2 = false;
        }
      break;

      case 2: // 6 ball auto 3 then 3
          if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThresh) {
            MagazinePower = 0.7;
            _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
          } else {
            _MagazineMotors.transmission->SetVoltage(0);
            _p1 = false;
          }
        }

        if (_p2) { // shoot 3 balls, the flywheel has already spun up
          if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThresh)
          MagazinePower = 0.7;
          _MagazineMotors.transmission->SetVoltage(12 * MagazinePower);
        } else {
          _MagazineMotors.transmission->SetVoltage(0);
          _p2 = false;
        }
      break;
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

  if (!MagOverride) {
    AutoMag();
  }

  // Shifting Mag up
  if (_contGroup.Get(ControlMap::ShiftUpMagazine)) {
    if (MagOverride) {
      MagazinePower = 1;
    } else {
      if (_Position5.GetAverageValue() <= ControlMap::MagazineBallThresh) {
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
      if (_Position5.GetAverageValue() < ControlMap::MagazineBallThresh) {
        MagazinePower = 0;
      } else {
        MagazinePower = -0.7;
      }
    }
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