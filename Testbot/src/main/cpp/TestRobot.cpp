#include "TestRobot.h"

#include "frc/AnalogInput.h"
#include <actuators/VoltageController.h>
#include "sensors/LimitSwitch.h"

#include <math.h>
#include <iostream>

using namespace frc;
using namespace wml;

double lastTimestamp;

using hand = frc::XboxController::JoystickHand;


void Robot::RobotInit() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

double kP = -0.3;
double kI = 0;
double kD = -0.01;

double PreviousError = 0;
double Sum = 0;
double goal = 0;

// Changables
double error;
double derror;

double Robot::PIDCalc(double dt, double input) {
  error = goal - input;
  derror = (error - PreviousError) / dt;
  Sum = Sum + error * dt;

  double output = kP * error + kI * Sum + kD * derror;

  PreviousError = error;
  return output;
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
