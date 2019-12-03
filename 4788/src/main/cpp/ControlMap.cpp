#include "ControlMap.h"

using hand = frc::XboxController::JoystickHand;

// using namespace frc;
using namespace wml;
using namespace wml::controllers;

// This is where you define which ports are used for your motors, pneumatics ect...

// -------------Defined Ports-------------------

// Controllers
#if __CONTROLMAP__USING_JOYSTICK__
  const int ControlMap::JoyController1Port = 1;
  const int ControlMap::JoyController2Port = 2;
#else
  const int ControlMap::XboxController1Port = 0;
  const int ControlMap::XboxController2Port = 1;
#endif

const double ControlMap::joyDeadzone = 0.05;


// Drive Left
const int ControlMap::DriveSRXportL = 1;
const int ControlMap::DriveSPXportL = 2;
// Drive Right
const int ControlMap::DriveSRXportR = 3;
const int ControlMap::DriveSPXportR = 4;

// Subsystem1
const int ControlMap::Sub1SRXport1 = 5;
const int ControlMap::Sub1SRXport2 = 6;

// Subsystem2
const int ControlMap::Sub2SPXport1 = 7;



// -------------Defined Speed---------------------

// Subsystem1
const double ControlMap::SubSystem1Speed = 0.3;

// Subsystem2
const double ControlMap::SubSystem2IdleSpeed = 0.1;
const double ControlMap::SubSystem2Speed = 0.9;



// -------------Defined Buttons-------------------

// Drivecar vroom vroom
#if __CONTROLMAP__USING_JOYSTICK__
  const tAxis ControlMap::DrivetrainForward{ 1, Joystick::kYAxis };
  const tAxis ControlMap::DrivetrainTurn{ 1, Joystick::kZAxis };
  const tButton ControlMap::ReverseDrivetrain{ 1, 2 };
#else
  const tAxis ControlMap::DrivetrainLeft{ 1, XboxController::kLeftYAxis };
  const tAxis ControlMap::DrivetrainRight{ 1, XboxController::kRightYAxis };
  const tButton ControlMap::ReverseDrivetrain{ 1, XboxController::kStart };
#endif


#if __CONTROLMAP__USING_JOYSTICK__
  // SubSystem1
  const tButton ControlMap::SubSystem1Up{ 1, 5 };
  const tButton ControlMap::SubSystem1Down{ 1, 6 };

  // SubSystem2
  const tButton ControlMap::SubSystem2Intake{ 1, 3 };
  const tButton ControlMap::SubSystem2Outtake{ 1, 4 };
#else 
  // SubSystem1
  const tButton ControlMap::SubSystem1Up{ 1, XboxController::kY };
  const tButton ControlMap::SubSystem1Down{ 1, XboxController::kB };

  // SubSystem2
  const tButton ControlMap::SubSystem2Intake{ 1, XboxController::kA };
  const tButton ControlMap::SubSystem2Outtake{ 1, XboxController::kX };
#endif
