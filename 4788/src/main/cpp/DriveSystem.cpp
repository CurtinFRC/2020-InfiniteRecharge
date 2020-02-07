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

    // Left Drive/ Acceleration
    if (fabs(_contGroup.Get(ControlMap::DrivetrainLeft)) > ControlMap::xboxDeadzone) { // I'm So fab
      // Forwards
      if (_contGroup.Get(ControlMap::DrivetrainLeft) < -(leftSpeed + ControlMap::MaxDrivetrainAcceleration)) {
        leftSpeed = leftSpeed + ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainLeft) < leftSpeed) {
        leftSpeed = fabs(_contGroup.Get(ControlMap::DrivetrainLeft));
      }
      // Reverse 
      if (-_contGroup.Get(ControlMap::DrivetrainLeft) < (leftSpeed - ControlMap::MaxDrivetrainAcceleration)) {
        leftSpeed = leftSpeed - ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainLeft) > leftSpeed) {
        leftSpeed = _contGroup.Get(ControlMap::DrivetrainLeft);
        leftSpeed = -leftSpeed;
      } 
    } else {
      leftSpeed = 0;
    }

    // Right Drive/ Acceleration
    if (fabs(_contGroup.Get(ControlMap::DrivetrainRight)) > ControlMap::xboxDeadzone) {
      // Forwards
      if (_contGroup.Get(ControlMap::DrivetrainRight) < -(rightSpeed + ControlMap::MaxDrivetrainAcceleration)) {
        rightSpeed = rightSpeed + ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainRight) < rightSpeed) {
        rightSpeed = fabs(_contGroup.Get(ControlMap::DrivetrainRight));
      }
      // Reverse
      if (-_contGroup.Get(ControlMap::DrivetrainRight) < (rightSpeed - ControlMap::MaxDrivetrainAcceleration)) {
        rightSpeed = rightSpeed - ControlMap::MaxDrivetrainAcceleration;
      } else if (_contGroup.Get(ControlMap::DrivetrainRight) > rightSpeed) {
        rightSpeed = _contGroup.Get(ControlMap::DrivetrainRight);
        rightSpeed = -rightSpeed;
      }
    } else {
      rightSpeed = 0;
    }


  #endif

  // _contGroup.GetController(ControlMap::Driver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 1);

  if (_contGroup.Get(ControlMap::ReverseDrivetrain, Controller::ONRISE)) {
    _drivetrain.SetInverted(!_drivetrain.GetInverted());
  }

  leftSpeed *= ControlMap::MaxDrivetrainSpeed;
  rightSpeed *= ControlMap::MaxDrivetrainSpeed;

  _drivetrain.Set(leftSpeed, rightSpeed);
}





// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, control::PIDGains gains) : _drivetrain(drivetrain), _pid(gains) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);
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

  if (!leftRevTest && !rightRevTest) {
    if (drivetest) {
      std::cout << "Drivetrain Test Successful" << std::endl;
      drivetest = false;
    }
  } else {
    // Left Test
    if (leftFwdTest) {
      if (_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() < ControlMap::DriveTestCaseRotations) {
        leftSpeed = 0.25;
      } else {
        leftSpeed = 0;
        leftFwdTest = false;
      }
    }
    if (!leftFwdTest) {
      if (_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() > 0) {
        leftSpeed = -0.25;
      } else {
        leftSpeed = 0;
        std::cout << "LeftDrive Return Successful" << std::endl;
        leftRevTest = false;
      }
    } 

    // Right Test
    if (rightFwdTest) {
      if (_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() > -ControlMap::DriveTestCaseRotations) {
        rightSpeed = 0.25;
      } else {
        rightSpeed = 0;
        rightFwdTest = false;
      }
    }
    if (!rightFwdTest) {
      if (_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() < 0) {
        rightSpeed = -0.25;
      } else {
        rightSpeed = 0;
        std::cout << "RightDrive Return Successful" << std::endl;
        rightRevTest = false;
      }
    } 

    std::cout << "LeftDrive Encoder " << _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() << std::endl;
    std::cout << "RightDrive Encoder " << _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() << std::endl;

  }
  _drivetrain.Set(leftSpeed, rightSpeed);
}