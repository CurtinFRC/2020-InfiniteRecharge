#include "Robot.h"

// Robot.cpp is our main entrypoint

// Note: If you try zero an encoder but the Motor controller is disconnected or doesn't exist
// The code will build, but it will not run on the robot. 

using namespace frc;
using namespace curtinfrc;

double lastTimestamp;

void Robot::RobotInit() {
  DriveSystem();
  SubSystem1(*robotMap);
  SubSystem2(controlMap->Sub2SPXport1);
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
  driveSystem->DriveControl();
  subSystem1->SubSystem1Control();
  subSystem2->SubSystem2Control();
} 

void Robot::TestInit() {
  driveSystem->zeroEncoder();
  subSystem1->zeroEncoder();
}
void Robot::TestPeriodic() {}