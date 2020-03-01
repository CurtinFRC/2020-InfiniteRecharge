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
                     _end(end) {
  // _StartMag.SetAverageBits(2);
  // _Position1.SetAverageBits(2);
  // _Position5.SetAverageBits(2);
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

  if (_p2) {
    timer.Start();
    if (timer.Get() <= BallTime3Shoot) {
      MagazinePower = 1;
    } else {
      MagazinePower = 0;
    }
    timer.Stop();
    timer.Reset();
    _p2 = false;
  }

  if (_p3) {
    timer.Start();
    if (timer.Get() <= Ball5Shoot) {
      MagazinePower = 1;
    } else {
      MagazinePower = 0;
    }
    timer.Stop();
    timer.Reset();
  _p2 = false;
  }

}

void MagLoader::TeleopOnUpdate(double dt) {

  // nt
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto MagTable = inst.GetTable("MagTable");
  // nt entry
  MagPower = MagTable->GetEntry("MagPower");
  MagEncoder = MagTable->GetEntry("MagEncoder");
  StartSensor = MagTable->GetEntry("StartSensor");
  SecondSensor = MagTable->GetEntry("SecondSensor");
  LastSensor = MagTable->GetEntry("LastSensor");
  Override = MagTable->GetEntry("Override");

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

  // Nt setting
  MagPower.SetDouble(MagazinePower);
  MagEncoder.SetDouble(_MagazineMotors.encoder->GetEncoderRotations());
  StartSensor.SetDouble(_StartMag.GetAverageValue());
  SecondSensor.SetDouble(_Position1.GetAverageValue());
  LastSensor.SetDouble(_Position5.GetAverageValue());
  Override.SetBoolean(MagOverride);


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