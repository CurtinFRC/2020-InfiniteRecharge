#include "Robot.h"

// Robot.cpp is our main entrypoint

using hand = frc::XboxController::JoystickHand;

double lastTimestamp;

double leftSpeed;
double rightSpeed;

wml::TalonSrx *left1;
wml::VictorSpx *left2;
wml::TalonSrx *right1;
wml::VictorSpx *right2;



void Robot::RobotInit() {
  xbox = new frc::XboxController(0);

  left1 = new wml::TalonSrx(3);
  left2 = new wml::VictorSpx(4);
  right1 = new wml::TalonSrx(1);
  right2 = new wml::VictorSpx(2);


  left1->SetInverted(true);
  left2->SetInverted(true);



  // leftMotor[0] = new frc::Spark(0);
  // leftMotor[0]->SetInverted(true);

  // rightMotor[0] = new frc::Spark(1);
  // rightMotor[0]->SetInverted(false);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  // leftMotor[0]->Set(xbox->kLeftYAxis);
  // rightMotor[0]->Set(xbox->kRightYAxis);
  if (xbox->GetAButton()) {
    leftSpeed = xbox->GetY(hand::kLeftHand);
    rightSpeed = xbox->GetY(hand::kRightHand);
  } else {
    leftSpeed = 0;
    rightSpeed = 0;
  }

  left1->Set(leftSpeed);
  left2->Set(leftSpeed);

  right1->Set(rightSpeed);
  right2->Set(rightSpeed);
} 

void Robot::TestInit() {}
void Robot::TestPeriodic() {}