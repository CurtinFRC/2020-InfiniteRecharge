#pragma once

#include "GeneralLibs/GeneralLibs.h"


#ifndef CONTROLMAP_H
#define CONTROLMAP_H

struct ControlMap {
	// ----------------Defined Ports----------------

	bool usingJoystick;

	// Controllers
	int XboxController1Port, XboxController2Port;
	int JoyController1Port, JoyController2Port;

	double joyDeadzone = 0.05;
	double xboxDeadzone = 0.05;

	// Drive System
	int DriveSRXportL, DriveSRXportR, DriveSPXportL, DriveSPXportR;

	// SubSystem1
	int Sub1SRXport1, Sub1SRXport2;

	// SubSystem2
	int Sub2SPXport1;

	// ---------------Defined Buttons---------------
	// SubSystem1
	bool SubSystem1Up, SubSystem1Down;

	// SubSystem2
	bool SubSystem2Intake, SubSystem2Outtake;

	// ------------------Instances------------------

	// Controllers
	frc::XboxController xbox1{ XboxController1Port };
	frc::XboxController xbox2{ XboxController2Port };
	frc::Joystick joy1{ JoyController1Port };
	frc::Joystick joy2{ JoyController2Port };
};

void DefinePorts();

#endif