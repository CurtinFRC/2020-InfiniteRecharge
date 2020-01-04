#pragma once

#include "controllers/Controllers.h"

#define __CONTROLMAP_USING_JOYSTICK__ true

struct ControlMap {
  // ---------------- Defined Ports ------------------

  // Controllers
  static const int XboxController1Port, XboxController2Port;
  static const int JoyController1Port, JoyController2Port;

  static const double joyDeadzone;
  static const double xboxDeadzone;
  static const double triggerDeadzone;

  // Drive System
  static const int DriveSRXportL, DriveSRXportR, DriveSPXportL, DriveSPXportR;


  // --------------- Defined Buttons -----------------

  // Drivetrain
  #if __CONTROLMAP_USING_JOYSTICK__
  static const wml::controllers::tAxis DrivetrainForward, DrivetrainTurn;
  #else
  static const wml::controllers::tAxis DrivetrainLeft, DrivetrainRight;
  #endif
  static const wml::controllers::tButton ReverseDrivetrain;


};
void DefinePorts();