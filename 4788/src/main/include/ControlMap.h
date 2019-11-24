#pragma once

#include "Robot.h"

class ControlMap : public frc::TimedRobot, protected curtinfrc::StrategyController, protected curtinfrc::NTProvider {
  public:

	// Controllers
	frc::XboxController *xbox1;
	frc::XboxController *xbox2;
	frc::Joystick *joy1;
	frc::Joystick *joy2;


	// -------------Defined Ports-------------------
	
	// Controllers
	static const int Controller1Port, Controller2Port;

	// Drive System
	static const int SRXportL, SRXportR, SPXportL, SPXportR;


	// -------------Function Definement----------------

	// Controllers
	ControlMap(int ControllerPort1_, int ControllerPort2_);
};