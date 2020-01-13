#include "TestRobot.h"

#include <actuators/VoltageController.h>

#include <math.h>
#include <iostream>

void Robot::RobotInit() {
  xbox = new wml::controllers::XboxController(0);

  LeftSRX = new wml::VictorSpx(8);
  LeftSPX = new wml::VictorSpx(3);
  LeftSRX->SetInverted(true);
  LeftSPX->SetInverted(true);

  RightSRX = new wml::TalonSrx(5);
  RightSPX = new wml::VictorSpx(4);
  RightSRX->SetInverted(false);
  RightSPX->SetInverted(false);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  if (xbox->GetAxis(wml::controllers::XboxController::kLeftThrottle)) {
    double speed = xbox->GetAxis(wml::controllers::XboxController::kLeftThrottle);
    LeftSRX->Set(speed);
    //LeftSPX->Set(1);
    //RightSRX->Set(1);
    //RightSPX->Set(1);
  } else {
    LeftSRX->Set(0);
    LeftSPX->Set(0);

    RightSRX->Set(0);
    RightSPX->Set(0);
  }
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
