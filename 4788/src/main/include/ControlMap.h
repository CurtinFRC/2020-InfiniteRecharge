#pragma once

#include "Robot.h"

#ifndef CONTROLMAP_H
#define CONTROLMAP_H

struct ControlMap {
	// ----------------Defined Ports----------------

	// Controllers
	int XboxController1Port, XboxController2Port;

	// Drive System
	int DriveSRXportL, DriveSRXportR, DriveSPXportL, DriveSPXportR;

	// SubSystem1
	int Sub1SRXport1, Sub1SRXport2;

	// SubSystem2
	int Sub2SPXport1;

	// ------------------Instances------------------

	// Controllers
	frc::XboxController xbox1{ XboxController1Port };
	frc::XboxController xbox2{ XboxController2Port };
	//frc::Joystick joy1{ JoyController1Port };
	//frc::Joystick joy2{ JoyController2Port };
};

void DefinePorts();

#endif