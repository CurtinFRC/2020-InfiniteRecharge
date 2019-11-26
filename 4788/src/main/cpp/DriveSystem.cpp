// #include "DriveSystem.h"
// #include "ControlMap.h"
// #include "Robot.h"

// using namespace curtinfrc;
// using namespace frc;
// using hand = frc::XboxController::JoystickHand; // can't be bothered writing it out complelty

// DriveSystem::DriveSystem(RobotMap *robotMap) {
//   // We invert one side of the motors to make it drive straight when both sides are positively/negatively active

//   // Initialise Left Drive Motors
//   robotMap->Lsrx.SetInverted(true);
//   robotMap->Lspx.SetInverted(true);

//   // Initialise Right Drive Motors
//   robotMap->Rsrx.SetInverted(false);
//   robotMap->Rspx.SetInverted(false);


//   drivetrain->StartLoop(100);

//   DriveSystem::ZeroEncoder();
// }

// void DriveSystem::ZeroEncoder() {
//   // Zero Encoders (Only SRX's Have encoders)
//   _robotmap->Lsrx.ZeroEncoder();
//   _robotmap->Rsrx.ZeroEncoder();
// }

// void DriveSystem::DriveControl() {
  
//   // Code if we are using joysticks
//   #if __CONTROLMAP__USING_JOYSTICK__

//   turn_speed = _robotmap->joy1.kYAxis;
//   left_speed = _robotmap->joy1.kYAxis + turn_speed;
//   right_speed = _robotmap->joy1.kZAxis - turn_speed;
//   drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

//   #else
//   left_speed = _robotmap->xbox1.kLeftYAxis/1.15;
//   right_speed = _robotmap->xbox1.kRightYAxis/1.15;
//   drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

//   #endif
// }