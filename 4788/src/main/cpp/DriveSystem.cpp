#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;


// Initializes & Defines groups for Manual Control
DrivetrainManual::DrivetrainManual(std::string name, 
                                   Drivetrain &drivetrain,
                                   wml::actuators::DoubleSolenoid &ChangeGears, 
                                   actuators::DoubleSolenoid &Shift2PTO, 
                                   frc::Servo &PTORatchetLeft,
                                   frc::Servo &PTORatchetRight,
                                   SmartControllerGroup &contGroup) : 
                                   
                                   Strategy(name),
                                   _drivetrain(drivetrain),
                                   _ChangeGears(ChangeGears), 
                                   _Shift2PTO(Shift2PTO), 
                                   _PTORatchetLeft(PTORatchetLeft),
                                   _PTORatchetRight(PTORatchetRight),
                                   _contGroup(contGroup) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(true);

  // nt
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto DriveTable = inst.GetTable("DriveTable");
  // nt entry
  LPower = DriveTable->GetEntry("LPower");
  RPower = DriveTable->GetEntry("RPower");
  LEC = DriveTable->GetEntry("LEC");
  REC = DriveTable->GetEntry("REC");
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

    if (fabs(_contGroup.Get(ControlMap::DrivetrainLeft)) > ControlMap::xboxDeadzone) {
      leftSpeed = _contGroup.Get(ControlMap::DrivetrainLeft);
      leftSpeed = -(fabs(leftSpeed) * leftSpeed);
    } else {
      leftSpeed = 0;
    }

    if (fabs(_contGroup.Get(ControlMap::DrivetrainRight)) > ControlMap::xboxDeadzone) {
      rightSpeed = _contGroup.Get(ControlMap::DrivetrainRight);
      rightSpeed = -(fabs(rightSpeed) * rightSpeed);
    } else {
      rightSpeed = 0;
    }


  #endif

  // Invert Drivebase
  if (_contGroup.Get(ControlMap::ReverseDrivetrain, Controller::ONRISE)) {
    _drivetrain.SetInverted(!_drivetrain.GetInverted());
  }

  // Shift Gear 
  if (_contGroup.Get(ControlMap::ShiftGears)) {
    _ChangeGears.SetTarget(actuators::BinaryActuatorState::kForward);
  } else {
    _ChangeGears.SetTarget(actuators::BinaryActuatorState::kReverse);
  }


  // PTO Toggle
  if (_contGroup.Get(ControlMap::Shift2PTO, Controller::ONRISE)) {
    if (!PTOactive) {
      PTOactive = true;
    } else {
      PTOactive = false;
    }
  }

  // PTO Shifter
  if (PTOactive) {
    if (_contGroup.Get(ControlMap::Servo)) {
      _Shift2PTO.SetTarget(actuators::BinaryActuatorState::kForward);
      _PTORatchetLeft.Set(ControlMap::PTORatchetLeftPosition);
      _PTORatchetRight.Set(ControlMap::PTORatchetRightPosition);
    }
  } else {
    _Shift2PTO.SetTarget(actuators::BinaryActuatorState::kReverse);
    _PTORatchetLeft.Set(ControlMap::PTORatchetLeftPositionInit);
    _PTORatchetRight.Set(ControlMap::PTORatchetRightPositionInit);
  }


  // Restrict the speed of the drivetrain
  leftSpeed *= ControlMap::MaxDrivetrainSpeed;
  rightSpeed *= ControlMap::MaxDrivetrainSpeed;

  // std::cout << "Speed " << leftSpeed << "," << rightSpeed << std::endl;

  LPower.SetDouble(leftSpeed);
  RPower.SetDouble(rightSpeed);
  LEC.SetDouble(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());
  REC.SetDouble(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations());

  // Update pneumatics
  _ChangeGears.Update(dt);
  _Shift2PTO.Update(dt);

  _drivetrain.Set(leftSpeed, rightSpeed);
}


// Initializes & Defines groups for Test Mode
DrivetrainTest::DrivetrainTest(Drivetrain &drivetrain, control::PIDGains gains) : _drivetrain(drivetrain), _pid(gains) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);
}

void DrivetrainTest::OnUpdate(double dt) {

  switch (testSelect) {
    case 1:
      if (_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() < ControlMap::DriveTestCaseRotations) {
        leftSpeed = 0.25;
      } else {
        leftSpeed = 0;
        testSelect++;
      }
    break;

    case 2:
      if (_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() > 0) {
        leftSpeed = -0.25;
      } else {
        leftSpeed = 0;
        std::cout << "LeftDrive Return Successful" << std::endl;
        testSelect++;
      }
    break;

    case 3:
      if (_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() > -ControlMap::DriveTestCaseRotations) {
        rightSpeed = 0.25;
      } else {
        rightSpeed = 0;
        testSelect++;
      }
    break;

    case 4:
      if (_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() < 0) {
        rightSpeed = -0.25;
      } else {
        rightSpeed = 0;
        std::cout << "RightDrive Return Successful" << std::endl;
        testSelect++;
      }
    break;
  }

  // std::cout << "LeftDrive Encoder " << _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() << std::endl;
  // std::cout << "RightDrive Encoder " << _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() << std::endl;

  _drivetrain.Set(leftSpeed, rightSpeed);
}