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
  static const int DriveMAXportFL, DriveMAXportFR, DriveMAXportBL, DriveMAXportBR;
  static const int ChangeGearPort1, ChangeGearPort2;
  static const double ChangeGearTime;
  static const double MaxDrivetrainSpeed;
  static const double MaxDrivetrainAcceleration;
  static const double DriveTestCaseRotations;

  // Turret
  static const bool TuneTurretPID;
  static const int TurretFlyWheelPort, TurretRotationPort, TurretAnglePort;
  static const int TurretLeftLimitPort, TurretRightLimitPort, TurretAngleDownLimitPort;
  static const bool TurretLeftLimitInvert, TurretRightLimitInvert, TurretAngleDownLimitInvert;
  static const double TurretDistanceSetpoint1, TurretDistanceSetpoint2, TurretDistanceSetpoint3;
  static const double TurretZeroTimeoutSeconds;
  static const double TurretEncoderSafeZone;
  static const double MaxTurretSpeed, MaxTurretAngularSpeed, FlyWheelVelocity;

  // Intake
  static const int IntakeMotorPort;
  static const int IntakeDownPort1, IntakeDownPort2;
  static const double PannelActuationTime;
  static const double IntakeDownActuationTime;

  // MagLoader
  static const int MagLoaderMotorPort;
  static const int StartMagLimitPort, Position1LimitPort, Position5LimitPort;
  static const double MagTestCaseRotations;

  //Control Pannel
  static const int ControlPannelPort;
  static const int ControlPannelUpPort;
  static const int ControlPannelUpSolPort1;
  static const int ControlPannelUpSolPort2;
  static const double ControlPannelActuationTime;

  // Climber
  static const int ClimberActuatorPort1, ClimberActuatorPort2;
  static const double ClimberActuationTime;
  static const int Shift2PTOPort, Shift2PTOForwardPosition, Shift2PTOReversePosition;
  static const int ClimberMotor1Port, ClimberMotor2Port;

  // Control System
  static const int PressureSensorPort;
  static const int CompressorPort;

  // --------------- Defined Buttons -----------------

  // PID Controller
  static const wml::controllers::tButton kpUP, kpDOWN;
  static const wml::controllers::tButton kiUP, kiDOWN;
  static const wml::controllers::tButton kdUP, kdDOWN;

  // Drivetrain
  #if __CONTROLMAP_USING_JOYSTICK__
  static const wml::controllers::tAxis DrivetrainForward, DrivetrainTurn;
  #else
  static const wml::controllers::tAxis DrivetrainLeft, DrivetrainRight;
  #endif
  static const wml::controllers::tButton ReverseDrivetrain;
  static const wml::controllers::tButton ShiftGears;

  // Turret
  #if __CONTROLMAP_USING_JOYSTICK__
  //@TODO
  #else
  static const wml::controllers::tAxis TurretAutoAimAxis;
  static const wml::controllers::tButton TurretAutoAim;

  static const wml::controllers::tAxis TurretManualRotate;
  static const wml::controllers::tAxis TurretManualAngle;
  static const wml::controllers::tAxis TurretFlyWheelSpinUp;
  static const wml::controllers::tButton TurretFire; // Might get rid of, if i automate Max speed of flywheel to fire.
  #endif

  // Intake
  #if __CONTROLMAP_USING_JOYSTICK__

  #else
  static const wml::controllers::tAxis Intake;
  static const wml::controllers::tAxis Outake;
  static const wml::controllers::tButton DownIntake;
  #endif

  //Wheel of Cringe 
  #if __CONTROLMAP_USING_JOYSTICK__

  #else 
  static const wml::controllers::tPOV ControlPannelUp;
  static const wml::controllers::tPOV SpinControlPannelLeft;
  static const wml::controllers::tPOV SpinControlPannelRight;
  static const wml::controllers::tPOV ControlPannelDown;

  #endif

  // MagLoader
  static const wml::controllers::tPOV ShiftMagazinePOV;

  static const wml::controllers::tButton ShiftUpMagazine;
  static const wml::controllers::tButton ShiftDownMagazine;

  // Climber
  #if __CONTROLMAP_USING_JOYSTICK__

  #else
  static const wml::controllers::tAxis ClimberControl;
  static const wml::controllers::tButton ClimberUp;
  static const wml::controllers::tButton ClimberDown;
  static const wml::controllers::tButton Shift2PTO;
  #endif
}; 