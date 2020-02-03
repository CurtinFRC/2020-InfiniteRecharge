#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;


// Initializes & Defines groups for Manual Control
DrivetrainManual::DrivetrainManual(std::string name, Drivetrain &drivetrain, wml::actuators::DoubleSolenoid &ChangeGears, SmartControllerGroup &contGroup) : Strategy(name), _drivetrain(drivetrain), _ChangeGears(ChangeGears), _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
}

// On Loop Update, this code runs (Just a drivebase)
void DrivetrainManual::OnUpdate(double dt) {

  #if __CONTROLMAP_USING_JOYSTICK__
    double joyForward = -_contGroup.Get(ControlMap::DrivetrainForward) * 0.9;
    double joyTurn = _contGroup.Get(ControlMap::DrivetrainTurn) * 0.6;
    joyForward = std::abs(joyForward);
    
    leftSpeed = joyForward + joyTurn;
    rightSpeed = joyForward - joyTurn;
  #else

    // Left Drive
    if (fabs(_contGroup.Get(ControlMap::DrivetrainLeft)) > ControlMap::xboxDeadzone) { // I'm So fab
      // Forwards
      if (_contGroup.Get(ControlMap::DrivetrainLeft) < -(leftSpeed + ControlMap::MaxDrivetrainAcceleration)) {
        leftSpeed = leftSpeed + ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainLeft) < leftSpeed) {
        leftSpeed = fabs(_contGroup.Get(ControlMap::DrivetrainLeft));
      }
      // Reverse 
      else if (_contGroup.Get(ControlMap::DrivetrainLeft) > (leftSpeed + ControlMap::MaxDrivetrainAcceleration)) {
        leftSpeed = leftSpeed - ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainLeft) > leftSpeed) {
        leftSpeed = _contGroup.Get(ControlMap::DrivetrainLeft);
        leftSpeed = -leftSpeed;
      } 
    } else {
      leftSpeed = 0;
    }

    // Right Drive
    if (fabs(_contGroup.Get(ControlMap::DrivetrainRight)) > ControlMap::xboxDeadzone) {
      // Forwards
      if (_contGroup.Get(ControlMap::DrivetrainRight) < -(rightSpeed + ControlMap::MaxDrivetrainAcceleration)) {
        rightSpeed = rightSpeed + ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainRight) < rightSpeed) {
        rightSpeed = fabs(_contGroup.Get(ControlMap::DrivetrainRight));
      }
      // Reverse
      else if (_contGroup.Get(ControlMap::DrivetrainRight) > (rightSpeed + ControlMap::MaxDrivetrainAcceleration)) {
        rightSpeed = rightSpeed - ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainRight) > rightSpeed) {
        rightSpeed = _contGroup.Get(ControlMap::DrivetrainRight);
        rightSpeed = -rightSpeed;
      }
    } else {
      rightSpeed = 0;
    }


  #endif

  if (_contGroup.Get(ControlMap::ReverseDrivetrain, Controller::ONRISE)) {
    _drivetrain.SetInverted(!_drivetrain.GetInverted());
  }

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




// Initializes & Defines groups for Test Mode
DrivetrainTest::DrivetrainTest(Drivetrain &drivetrain, control::PIDGains gains) : _drivetrain(drivetrain), _pid(gains) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);
}

void DrivetrainTest::OnUpdate(double dt) {
  //@TODO Just drive forwards and backwards using encoders. Then make some outputs to make sure everything is working
}