#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;


// Initializes & Defines groups for Manual Control
DrivetrainManual::DrivetrainManual(std::string name, 
                                   Drivetrain &drivetrain, 
                                   wml::actuators::DoubleSolenoid &ChangeGears, 
                                   actuators::DoubleSolenoid &Shift2PTO, 
                                   SmartControllerGroup &contGroup) : 
                                   
                                   Strategy(name), 
                                   _drivetrain(drivetrain), 
                                   _ChangeGears(ChangeGears), 
                                   _Shift2PTO(Shift2PTO), 
                                   _contGroup(contGroup) {
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

  if (_contGroup.Get(ControlMap::ReverseDrivetrain, Controller::ONRISE)) {
    _drivetrain.SetInverted(!_drivetrain.GetInverted());
  }

  if (_contGroup.Get(ControlMap::ShiftGears)) {
    _ChangeGears.SetTarget(actuators::BinaryActuatorState::kForward);
    std::cout << "Shift Gears" << std::endl;
  } else {
    _ChangeGears.SetTarget(actuators::BinaryActuatorState::kReverse);
    // std::cout << "Not Shifting Gears" << std::endl;
  }

  _ChangeGears.Update(dt);

  leftSpeed *= ControlMap::MaxDrivetrainSpeed;
  rightSpeed *= ControlMap::MaxDrivetrainSpeed;

  _drivetrain.Set(leftSpeed, rightSpeed);
}

// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, 
                               control::PIDGains gains,
                               int &autoSelector,
                               bool &strt,
                               bool &p1,
                               bool &p2,
                               bool &p3,
                               bool &end) : 
                               
                               _drivetrain(drivetrain), 
                               _pid(gains),
                               _autoSelector(autoSelector),
                               _strt(strt),
                               _p1(p1),
                               _p2(p2),
                               _p3(p3),
                               _end(end) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);
}

void Rotation2Point(double *DistanceInRotations, double p1x, double p1y, double p2x, double p2y) {}

double leftPreviousError = 0;
double rightPreviousError = 0;
double leftSum = 0;
double rightSum = 0;

double AutoPID(double dt, double goal, double input, double kp, double ki, double kd, double *previousError, double *sum) {
  double error = goal - input;
  double derror = (error - *previousError) / dt;
  *sum = *sum + error * dt;  

   double output = kp * error + ki * *sum + kd * derror;

  *previousError = error;
  return output;
} 

void DrivetrainAuto::OnUpdate(double dt) {
  double leftPower, rightPower;
  double DistanceInRotations;
  switch (_autoSelector) {
    case 1: // Auto 1
      Rotation2Point(&DistanceInRotations, ControlMap::Strt6Ballx, ControlMap::Strt6Bally, ControlMap::wypt1Ball8x, ControlMap::wypt1Ball8y);
      if (!_strt) {
        if ((_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() < DistanceInRotations) || (_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() < DistanceInRotations)) {
          leftPower = AutoPID(dt, 
                              DistanceInRotations, 
                              _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations(), 
                              ControlMap::leftKp,
                              ControlMap::leftKi,
                              ControlMap::leftKd,
                              &leftPreviousError,
                              &leftSum);
          rightPower = AutoPID(dt, 
                               DistanceInRotations, 
                               _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations(),
                               ControlMap::rightKp,
                               ControlMap::rightKi,
                               ControlMap::rightKd,
                               &rightPreviousError,
                               &rightSum);
        } else {
          _strt = true;
        }
      }
      break;
    case 2: // Auto 2

      break;
    case 3: // Auto 3

      break;
    case 4: // Auto 4

      break;
    case 5: // Auto 5
  }

  _drivetrain.Set(leftPower, rightPower);
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