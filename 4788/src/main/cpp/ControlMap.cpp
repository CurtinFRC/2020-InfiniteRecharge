#include "ControlMap.h"
#include "Robot.h"

using hand = frc::XboxController::JoystickHand;

using namespace frc;
using namespace curtinfrc;

// This is where you define which ports are used for your motors, pneumatics ect...

// -------------Defined Ports-------------------
void DefinePorts() {
  ControlMap CtrlMp;

  CtrlMp.usingJoystick = false;

  // Controllers
  if (CtrlMp.usingJoystick) {
    CtrlMp.JoyController1Port = 1;
    CtrlMp.JoyController2Port = 2;
  } else {
    CtrlMp.XboxController1Port = 0;
    CtrlMp.XboxController2Port = 1;
  }

  // Drive Left
  CtrlMp.DriveSRXportL = 1;
  CtrlMp.DriveSPXportL = 2;
  // Drive Right
  CtrlMp.DriveSRXportR = 3;
  CtrlMp.DriveSPXportR = 4;

  // Subsystem1
  CtrlMp.Sub1SRXport1 = 5;
  CtrlMp.Sub1SRXport2 = 6;

  // Subsystem2
  CtrlMp.Sub2SPXport1 = 7;

// -------------Defined Buttons-------------------

  if (CtrlMp.usingJoystick) {
    // SubSystem1
    CtrlMp.SubSystem1Up = CtrlMp.joy1.GetRawButton(5);
    CtrlMp.SubSystem1Down = CtrlMp.joy1.GetRawButton(6);

    // SubSystem2
    CtrlMp.SubSystem2Intake = CtrlMp.joy1.GetRawButton(1);
    CtrlMp.SubSystem2Outtake = CtrlMp.joy1.GetRawButton(2);
  } else {
    // SubSystem1
    CtrlMp.SubSystem1Up = CtrlMp.xbox1.GetYButton();
    CtrlMp.SubSystem1Down = CtrlMp.xbox1.GetBButton();

    // SubSystem2
    CtrlMp.SubSystem2Intake = CtrlMp.xbox1.GetAButton();
    CtrlMp.SubSystem2Outtake = CtrlMp.xbox1.GetXButton();
  }

}