#include "Robot.h"

// Local Files
#include "DriveSystem.h"
#include "ControlMap.h"
#include "SubSystem1.h"
#include "SubSystem2.h"
#include "PenumaticSystem1.h"
#include "PenumaticSystem2.h"

// Common Files
#include "strategy/MPStrategy.h"

#include <math.h>
#include <iostream>

// FRC Files
#include <cameraserver/CameraServer.h>
#include <frc/DriverStation.h> 

// Robot.cpp is our main entrypoint

// Note: If you try zero an encoder but the Motor controller is disconnected or doesn't exist
// The code will build, but it will not run on the robot. 

using namespace frc;
using namespace curtinfrc;

double lastTimestamp;

void Robot::RobotInit() {
  ControlMap CtrlMp;
  DefinePorts();
  DriveSystem(CtrlMp.DriveSRXportL, CtrlMp.DriveSRXportR, CtrlMp.DriveSPXportL, CtrlMp.DriveSPXportR);
  SubSystem1(CtrlMp.Sub1SRXport1, CtrlMp.Sub1SRXport2);
  SubSystem2(CtrlMp.Sub2SPXport1);
  //compressor = new curtinfrc::actuators::DoubleSolenoid;

  std::cout << "Robot SetUp Complete" << std::endl;
}


void Robot::RobotPeriodic() {
  // In periodic mode. Continuous looped code
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {
  driveSystem->zeroEncoder();
  subSystem1->zeroEncoder();
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  driveSystem->zeroEncoder();
  subSystem1->zeroEncoder();
}
void Robot::TeleopPeriodic() {
  // when enabled. this code runs
} 

void Robot::TestInit() {
  driveSystem->zeroEncoder();
  subSystem1->zeroEncoder();
}
void Robot::TestPeriodic() {}