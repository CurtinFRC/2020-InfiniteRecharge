#include "ControlMap.h"
#include "Robot.h"
#include "RobotMap.h"

#include "controllers/CurtinControllers.h"

using hand = frc::XboxController::JoystickHand;

using namespace frc;
using namespace curtinfrc;

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

// -------------Defined Buttons-------------------

#if __CONTROLMAP__USING_JOYSTICK__
  // SubSystem1
  const int ControlMap::SubSystem1Up = 5;
  const int ControlMap::SubSystem1Down = 6;

  // SubSystem2
  const int ControlMap::SubSystem2Intake = 3;
  const int ControlMap::SubSystem2Outtake = 4;
#else 
  // SubSystem1
  const int ControlMap::SubSystem1Up = curtinfrc::controllers::XboxController::kY;
  const int ControlMap::SubSystem1Down = curtinfrc::controllers::XboxController::kB;              

  // SubSystem2
  const int ControlMap::SubSystem2Intake = curtinfrc::controllers::XboxController::kA;
  const int ControlMap::SubSystem2Outtake = curtinfrc::controllers::XboxController::kX;
#endif