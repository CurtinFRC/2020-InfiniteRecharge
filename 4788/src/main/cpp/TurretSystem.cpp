#include <iostream>
#include "TurretSystem.h"

using namespace wml;
using namespace wml::controllers;

double TurretTurnSpeed;
double TurretAngleSpeed;
double TurretFlyWheelSpeed;

// Initializes & Defines groups for Manual/Teleop Control
TurretTeleop::TurretTeleop(std::string name, Turret &turret, SmartControllerGroup &contGroup) : Strategy(name), _turret(turret), _contGroup(contGroup) {
  Requires(&turret);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the turret)
void TurretTeleop::OnUpdate(double dt) {
  // // Manual Turret Rotate
  // if (_contGroup.Get(ControlMap::TurretManualRotate) >= ControlMap::triggerDeadzone) {
  //   TurretTurnSpeed = _contGroup.Get(ControlMap::TurretManualRotate);
  // } else {
  //   TurretTurnSpeed = 0;
  // }

  // // Manual Turret Angle
  // if (_contGroup.Get(ControlMap::TurretManualAngle) >= ControlMap::triggerDeadzone) {
  //   robotMap.turret.TurretAngle.Set(_contGroup.Get(ControlMap::TurretManualAngle));
  // } else {
  //   TurretAngleSpeed = 0;
  // }

  // // Auto Aiming Code
  // if (_contGroup.Get(ControlMap::TurretAutoAim) >= ControlMap::triggerDeadzone) {
  //   if ((TargetXGet >= ImageWidthGet) || (TargetYGet >= ImageHeightGet)) {
  //     std::cout << "Vision Tracking Artificating Error" << std::endl;
  //     //@TODO create vibration on controller. (Flashing Vibration)
  //   } else {
  //     std::cout << "Auto Aiming Active" << std::endl;
  //     TurretTurnSpeed = TargetXGet/ImageWidthGet;
  //     TurretAngleSpeed = TargetYGet/ImageHeightGet;
  //   } 
  // } 

  // // FlyWheel Code
  // if (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) >= ControlMap::triggerDeadzone) {
  //   TurretFlyWheelSpeed = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
  // } else {
  //   TurretFlyWheelSpeed = 0;
  // }

  // robotMap.turret.TurretAngle.Set(TurretAngleSpeed);
  // robotMap.turret.TurretRotation.Set(TurretTurnSpeed);
  // robotMap.turret.TurretFlyWheel.Set(TurretFlyWheelSpeed);
  _turret.Set(1,1);
}







// Initializes & Defines groups for Auto Control
TurretAuto::TurretAuto(std::string name) : Strategy(name) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just the turret)
void TurretAuto::OnUpdate(double dt) {
  //@TODO auto aim during autonomous. (still working on pathweaver)
}






TurretTest::TurretTest(std::string name) : Strategy(name) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

void TurretTest::OnUpdate(double dt) {
  //@TODO zero encoders activate motors and if it's getting vision tracking values. Basically... a test. lol
}