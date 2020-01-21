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

  static const int Driver = 1;
  static const int CoDriver = 2;

  static const double joyDeadzone;
  static const double xboxDeadzone;
  static const double triggerDeadzone;

  // Drive System
  static const int DriveSRXportL, DriveSRXportR, DriveSPXportL, DriveSPXportR;

  // Turret
  static const int TurretFlyWheelPort, TurretRotationPort, TurretAnglePort;

  // Intake
  static const int IntakeMotorPort;

  // MagLoader
  static const int MagLoaderMotorPort;
  static const int StartMagLimitPort;
  static const int Position1LimitPort;
  static const int Position5LimitPort;

  //Wheel of Cringe 
  static const int ControlPannelPort;

  // Climber
  static const int ClimberActuatorPort1, ClimberActuatorPort2;
  static const double ClimberActuationTime;

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

  // Turret
  #if __CONTROLMAP_USING_JOYSTICK__
  //@TODO
  #else
  static const wml::controllers::tAxis TurretAutoAim;
  static const wml::controllers::tAxis TurretManualRotate;
  static const wml::controllers::tAxis TurretManualAngle;
  static const wml::controllers::tAxis TurretFlyWheelSpinUp;
  static const wml::controllers::tButton TurretFire; // Might get rid of, if i automate Max speed of flywheel to fire.
  #endif

  // Intake
  #if __CONTROLMAP_USING_JOYSTICK__
  static const wml::controllers::tButton Intake;
  static const wml::controllers::tButton Outake;
  #else
  static const wml::controllers::tAxis Intake;
  static const wml::controllers::tAxis Outake;
  #endif

  //Wheel of Cringe 
  #if __CONTROLMAP_USING_JOYSTICK__

  #else 
  static const wml::controllers::tPOV ControlPannelUp;
  static const wml::controllers::tPOV SpinControlPannel;
  #endif

  // MagLoader
  #if __CONTROLMAP_USING_JOYSTICK__

  #else
  static const wml::controllers::tButton ShiftUpMagazine;
  static const wml::controllers::tButton ShiftDownMagazine;
  #endif


  // Climber
  #if __CONTROLMAP_USING_JOYSTICK__

  #else
  static const wml::controllers::tButton ClimberUp;
  static const wml::controllers::tButton ClumberDown;
  #endif
};