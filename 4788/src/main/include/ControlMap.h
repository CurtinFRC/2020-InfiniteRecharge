#pragma once

// #include "GeneralLibs/GeneralLibs.h"
#include "controllers/Controllers.h"

#define __CONTROLMAP__USING_JOYSTICK__ true

struct ControlMap {
	// ----------------Defined Ports----------------

	// Controllers
	static const int XboxController1Port, XboxController2Port;
	static const int JoyController1Port, JoyController2Port;

	static const double joyDeadzone;
	static const double xboxDeadzone;

	// Drive System
	static const int DriveSRXportL, DriveSRXportR, DriveSPXportL, DriveSPXportR;

	// SubSystem1
	static const int Sub1SRXport1, Sub1SRXport2;

	// SubSystem2
	static const int Sub2SPXport1;

	// ---------------Defined Buttons---------------
	// DriveCar vroom vroom
	#if __CONTROLMAP__USING_JOYSTICK__
	static const wml::controllers::tAxis DrivetrainForward, DrivetrainTurn;
	#else
	static const wml::controllers::tAxis DrivetrainLeft, DrivetrainRight;
	#endif
	static const wml::controllers::tButton ReverseDrivetrain;
	
	// SubSystem1
	static const wml::controllers::tButton SubSystem1Up, SubSystem1Down;

	// SubSystem2
	static const wml::controllers::tButton SubSystem2Intake, SubSystem2Outtake;
};
void DefinePorts();
