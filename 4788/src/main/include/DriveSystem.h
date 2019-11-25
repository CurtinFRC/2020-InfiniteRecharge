#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"
#include "RobotMap.h"

class DriveSystem {
  public:

	// -------------Drive Definement----------------
  curtinfrc::Gearbox *left_Gearbox, *right_Gearbox;
  curtinfrc::Drivetrain *drivetrain;
  double left_speed;
  double right_speed;
  double turn_speed;

  // -------------Function Definement----------------
  DriveSystem(); 
  void zeroEncoder();
  void DriveControl();

 private:
  RobotMap *_robotmap;
};