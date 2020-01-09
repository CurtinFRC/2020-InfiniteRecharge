#include "DriveSystem.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

RobotMap::ControlSystem controlSystem;

// Initializes & Defines groups for Manual Control
DrivetrainManual::DrivetrainManual(std::string name, Drivetrain &drivetrain, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just a drivebase)
void DrivetrainManual::OnUpdate(double dt) {
  double leftSpeed, rightSpeed;

  #if __CONTROLMAP_USING_JOYSTICK__
    double joyForward = -_cont1.Get(ControlMap::DrivetrainForward) * 0.9;
    double joyTurn = _cont1.Get(ControlMap::DrivetrainTurn) * 0.6;
    joyForward = std::abs(joyForward);
    
    leftSpeed = joyForward + joyTurn;
    rightSpeed = joyForward - joyTurn;
  #else
    leftSpeed = -_contGroup.Get(ControlMap::DrivetrainLeft);
    rightSpeed = -_contGroup.Get(ControlMap::DrivetrainRight);
  #endif

  if (_contGroup.Get(ControlMap::DriveToVisionTarget)) {
    leftSpeed = controlSystem.TargetX.GetDouble(0);
    rightSpeed = -controlSystem.TargetX.GetDouble(0);
  }

  if (_contGroup.Get(ControlMap::ReverseDrivetrain, Controller::ONRISE))
    _drivetrain.SetInverted(!_drivetrain.GetInverted());

  _drivetrain.Set(leftSpeed, rightSpeed);
}

// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, control::PIDGains gains) : _drivetrain(drivetrain), _pid(gains) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);
  //@TODO PID stuff. which i will do in a few weeks when i have a working robot
}

void DrivetrainAuto::OnUpdate(double dt) {
  //@TODO, Everthing to do with autonomous basically... so yea, i'm looking forward to that
}
