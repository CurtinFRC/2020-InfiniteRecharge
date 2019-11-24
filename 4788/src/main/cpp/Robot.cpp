#include "ControlMap.h"
#include "Robot.h"
#include "DriveSystem.h"

#include "strategy/MPStrategy.h"

#include <math.h>
#include <iostream>

#include <cameraserver/CameraServer.h>

#include <frc/DriverStation.h>

// Note: If you try zero an encoder but the Motor controller is disconnected or doesn't exist
// The code will build, but it will not run on the robot. 

using namespace frc;
using namespace curtinfrc;

double lastTimestamp;

void Robot::RobotInit() {
  ControlMap CtrlMp;
  DefinePorts();
  DriveSystem(CtrlMp.SRXportL, CtrlMp.SRXportR, CtrlMp.SPXportL, CtrlMp.SPXportR);
  //compressor = new curtinfrc::actuators::DoubleSolenoid;

  std::cout << "Robot SetUp Complete" << std::endl;
}


void Robot::RobotPeriodic() {
  // In periodic mode. Continuous looped code
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  // when enabled. this code runs
} 

void Robot::TestInit() {}
void Robot::TestPeriodic() {}