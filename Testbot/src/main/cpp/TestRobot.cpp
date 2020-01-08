#include "TestRobot.h"

#include <actuators/VoltageController.h>

#include <math.h>
#include <iostream>

void Robot::RobotInit() {
  xbox = new wml::controllers::XboxController(0);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  if (xbox->kA) {
    // do stuff if A button pressed
  } else {
    // do stuff if button is NOT pressed
  }
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
