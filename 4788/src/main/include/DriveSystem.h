#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"

class DriveSystem {
  public:

  /* 
    Sometimes we mix both SRX & SPX Controllers
    Because it wastes SRX's as they have encoders
    where as SPX's do not. Which can be used in PID & Automation
  */

  // ----------------Instances--------------------
  ControlMap *controlMap;

	// -------------Drive Definement----------------
  curtinfrc::Gearbox *left_Gearbox, *right_Gearbox;
  curtinfrc::Drivetrain *drivetrain;
  double left_speed;
  double right_speed;
  double turn_speed;

  curtinfrc::TalonSrx *DriveMotorLsrx, *DriveMotorRsrx;
  curtinfrc::VictorSpx *DriveMotorLspx, *DriveMotorRspx;

  // -------------Function Definement----------------
  DriveSystem(int SRXportL_, int SRXportR_, int SPXportL_, int SPXportR_);
  void zeroEncoder();
  void DriveControl();
};