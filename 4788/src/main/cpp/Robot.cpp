#include "Robot.h"
#include "ControlMap.h"
#include "DriveSystem.h"

#include "strategy/MPStrategy.h"

#include <math.h>
#include <iostream>

#include <cameraserver/CameraServer.h>

#include <frc/DriverStation.h>

using namespace frc;
using namespace curtinfrc;

double lastTimestamp;

void Robot::RobotInit() {
  // when the robot is initilized
  ControlMap(ControlMap::Controller1Port, ControlMap::Controller2Port);

  DriveSystem(ControlMap::SRXportL, ControlMap::SRXportR, ControlMap::SPXportL, ControlMap::SPXportR);
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