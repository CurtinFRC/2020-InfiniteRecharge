#include "DriveSystem.h"
#include "RobotMap.h"

#include <cmath>

using namespace wml;
using namespace wml::controllers;

RobotMap::ControlSystem controlSystem;

DrivetrainManual::DrivetrainManual(std::string name, Drivetrain &drivetrain, SmartController &cont1, SmartController &cont2) : Strategy(name), _drivetrain(drivetrain), _cont1(cont1), _cont2(cont2) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

void DrivetrainManual::OnUpdate(double dt) {
  double leftSpeed, rightSpeed;

  #if __CONTROLMAP_USING_JOYSTICK__
    double joyForward = -_cont1.Get(ControlMap::DrivetrainForward) * 0.9;
    double joyTurn = _cont1.Get(ControlMap::DrivetrainTurn) * 0.6;
    joyForward = std::abs(joyForward);
    
    leftSpeed = joyForward + joyTurn;
    rightSpeed = joyForward - joyTurn;
  #else
    leftSpeed = -_cont1.Get(ControlMap::DrivetrainLeft);
    rightSpeed = -_cont1.Get(ControlMap::DrivetrainRight);
  #endif

  if (_cont1.Get(ControlMap::DriveToVisionTarget)) {
    leftSpeed = controlSystem.TargetX.GetDouble(0);
    rightSpeed = -controlSystem.TargetX.GetDouble(0);
  }

  if (_cont1.Get(ControlMap::ReverseDrivetrain, Controller::ONRISE))
    _drivetrain.SetInverted(!_drivetrain.GetInverted());

  _drivetrain.Set(leftSpeed, rightSpeed);
}
