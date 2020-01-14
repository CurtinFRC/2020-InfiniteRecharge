#pragma once

#include <vector>

#include "controllers/Controllers.h"

#define __CONTROLMAP_USING_JOYSTICK__ false

struct ControlMap {
  static void InitSmartControllerGroup(wml::controllers::SmartControllerGroup &contGroup);
  // ---------------- Defined Ports ------------------

  // Controllers
  static const int XboxController1Port, XboxController2Port;
  static const int JoyController1Port, JoyController2Port;

  static const double joyDeadzone;
  static const double xboxDeadzone;
  static const double triggerDeadzone;

  // Drive System
  static const int DriveSRXportL, DriveSRXportR, DriveSPXportL, DriveSPXportR;

  //Intake system 
  static const int Lintake, Rintake, Mintake;

  //Climber system 
  //static const int ClimberMotor;

  // Control System
  static const int PressureSensorPort;
  static const int CompressorPort;


  // --------------- Defined Buttons -----------------

  // Drivetrain
  #if __CONTROLMAP_USING_JOYSTICK__
  static const wml::controllers::tAxis DrivetrainForward, DrivetrainTurn;
  #else
  static const wml::controllers::tAxis DrivetrainLeft, DrivetrainRight;
  #endif
  static const wml::controllers::tButton ReverseDrivetrain;

  // Intake
  static const wml::controllers::tAxis IntakeIn;
  static const wml::controllers::tAxis IntakeOut;

  // Climber system 
  //static const wml::controllers::tButton UpMiddle;
  //static const wml::controllers::tButton UpFull;
  //static const wml::controllers::tButton UpClimb;
  //static const wml::controllers::tButton DownClimb;
};