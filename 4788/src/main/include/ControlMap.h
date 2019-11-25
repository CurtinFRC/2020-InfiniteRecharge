#include "GeneralLibs/GeneralLibs.h"


#ifndef CONTROLMAP_H
#define CONTROLMAP_H

#define __CONTROLMAP__USING_JOYSTICK__ false

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
	// SubSystem1
	static const int SubSystem1Up, SubSystem1Down;

	// SubSystem2
	static const int SubSystem2Intake, SubSystem2Outtake;
};
void DefinePorts();

#endif