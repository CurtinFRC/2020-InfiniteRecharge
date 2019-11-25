#include "DriveSystem.h"
#include "ControlMap.h"
#include "Robot.h"

using namespace curtinfrc;
using namespace frc;
using hand = frc::XboxController::JoystickHand; // can't be bothered writing it out complelty

DriveSystem::DriveSystem() {
  // We invert one side of the motors to make it drive straight when both sides are positively/negatively active

  // Initialise Left Drive Motors
  _robotmap->DriveMotorLsrx.SetInverted(true);
  _robotmap->DriveMotorLspx.SetInverted(true);

  // Initialise Right Drive Motors
  _robotmap->DriveMotorRsrx.SetInverted(false);
  _robotmap->DriveMotorRspx.SetInverted(false);

  // Gearboxes are pairs of motors e.g left srx and spx  
  left_Gearbox = new Gearbox{ new curtinfrc::actuators::MotorVoltageController(new SpeedControllerGroup(_robotmap->DriveMotorLsrx, _robotmap->DriveMotorLspx)), nullptr };
  right_Gearbox = new Gearbox{ new curtinfrc::actuators::MotorVoltageController(new SpeedControllerGroup(_robotmap->DriveMotorRsrx, _robotmap->DriveMotorRspx)), nullptr };

  // Drivetrain is left and right combined.
  DrivetrainConfig drivetrainConfig{ *left_Gearbox, *right_Gearbox };
  drivetrain = new Drivetrain(drivetrainConfig);
  drivetrain->StartLoop(100);

  DriveSystem::zeroEncoder();
}

void DriveSystem::zeroEncoder() {
  // Zero Encoders (Only SRX's Have encoders)
  _robotmap->DriveMotorLsrx.ZeroEncoder();
  _robotmap->DriveMotorRsrx.ZeroEncoder();
}

void DriveSystem::DriveControl() {
  
  // Code if we are using joysticks
  #if __CONTROLMAP__USING_JOYSTICK__

  turn_speed = _robotmap->joy1.kYAxis;
  left_speed = _robotmap->joy1.kYAxis + turn_speed;
  right_speed = _robotmap->joy1.kZAxis - turn_speed;
  drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

  #else
  left_speed = _robotmap->xbox1.kLeftYAxis/1.15;
  right_speed = _robotmap->xbox1.kRightYAxis/1.15;
  drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

  #endif
}