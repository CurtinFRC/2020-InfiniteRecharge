#include "DriveSystem.h"
#include "ControlMap.h"
#include "Robot.h"

using namespace curtinfrc;
using namespace frc;
using hand = frc::XboxController::JoystickHand; // can't be bothered writing it out complelty

DriveSystem::DriveSystem(int SRXportL_, int SRXportR_, int SPXportL_, int SPXportR_) {

  // We invert one side of the motors to make it drive straight when both sides are positively/negatively active

  // Initialise Left Drive Motors
  DriveMotorLsrx = new curtinfrc::TalonSrx(SRXportL_);
  DriveMotorLspx = new curtinfrc::VictorSpx(SPXportL_);
  DriveMotorLsrx->SetInverted(true);
  DriveMotorLspx->SetInverted(true);

  // Initialise Right Drive Motors
  DriveMotorRsrx = new curtinfrc::TalonSrx(SRXportR_);
  DriveMotorRspx = new curtinfrc::VictorSpx(SPXportR_);
  DriveMotorRsrx->SetInverted(false);
  DriveMotorRspx->SetInverted(false);

  // Gearboxes are pairs of motors e.g left srx and spx
  left_Gearbox = new Gearbox{ new curtinfrc::actuators::MotorVoltageController(new SpeedControllerGroup(*DriveMotorLsrx, *DriveMotorLspx)), nullptr };
  right_Gearbox = new Gearbox{ new curtinfrc::actuators::MotorVoltageController(new SpeedControllerGroup(*DriveMotorRsrx, *DriveMotorRspx)), nullptr };

  // Drivetrain is left and right combined.
  DrivetrainConfig drivetrainConfig{ *left_Gearbox, *right_Gearbox };
  drivetrain = new Drivetrain(drivetrainConfig);
  drivetrain->StartLoop(100);

  DriveSystem::zeroEncoder();
}

void DriveSystem::zeroEncoder() {
  // Zero Encoders (Only SRX's Have encoders)
  DriveMotorLsrx->ZeroEncoder();
  DriveMotorRsrx->ZeroEncoder();
}

void DriveSystem::DriveControl() {
  
  // Code if we are using joysticks
  if (controlMap->usingJoystick) {
    turn_speed = controlMap->joy1.GetY();
    left_speed = controlMap->joy1.GetY() + turn_speed;
    right_speed = controlMap->joy1.GetZ() - turn_speed;
    drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

  // Code if we are using Xbox Controllers
  } else {
    left_speed = controlMap->xbox1.GetY(hand::kLeftHand)/1.15;
    right_speed = controlMap->xbox1.GetY(hand::kRightHand)/1.15;
    drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));
  }
}