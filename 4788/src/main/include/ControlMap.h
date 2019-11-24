#pragma once

#include "Robot.h"

#ifndef CONTROLMAP_H
#define CONTROLMAP_H

struct ControlMap {
	// ----------------Defined Ports----------------

	// Controllers
	int XboxController1Port, XboxController2Port;

	// Drive System
	int SRXportL, SRXportR, SPXportL, SPXportR;

	// ------------------Instances------------------

	// Controllers
	frc::XboxController xbox1{ XboxController1Port };
	frc::XboxController xbox2{ XboxController2Port };
	//frc::Joystick joy1{ JoyController1Port };
	//frc::Joystick joy2{ JoyController2Port };
};

void DefinePorts();

#endif