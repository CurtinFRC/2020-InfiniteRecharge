#include "TestRobot.h"

#include <actuators/VoltageController.h>

#include <math.h>
#include <iostream>

using namespace frc;
using namespace wml;

void Robot::RobotInit() {
  xbox = new wml::controllers::XboxController(0);
  
  leftMotors = new TalonSrx(2);
  leftMotors->SetInverted(false);
  //left = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*leftMotors)), nullptr};

  rightMotors= new TalonSrx(5);
  rightMotors->SetInverted(true);
  //right = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*rightMotors)), nullptr};

  hatchEjector = new DoubleSolenoid(0, 1);

  DrivetrainConfig drivetrainConfig{*left, *right};
  drivetrain = new Drivetrain(drivetrainConfig);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto visionTable = inst.GetTable("VisionTracking");
	auto table = visionTable->GetSubTable("Target");

  double Xoffset = table->GetNumber("Target_X", 0);
  double Yoffset = table->GetNumber("Target_Y", 0);
  double ImageHeight = table->GetNumber("ImageHeight", 0);
  double ImageWidth = table->GetNumber("ImageWidth", 0);


  std::cout << "X,Y: " << Xoffset << "," << Yoffset << std::endl;

  Xoffset = Xoffset/ImageWidth;
  Yoffset = Yoffset/ImageHeight;
  
  double leftSpeed = -xbox->GetAxis(1); // L Y axis
  double rightSpeed = -xbox->GetAxis(5); // R Y axis

  leftSpeed = Xoffset;
  rightSpeed = -Xoffset;

  leftSpeed *= fabs(leftSpeed);
  rightSpeed *= fabs(rightSpeed);

  leftMotors->Set(leftSpeed);
  rightMotors->Set(rightSpeed);



  //drivetrain->Set(leftSpeed, rightSpeed);

  hatchEjector->Set(!xbox->GetButton(6) ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse); // R bumper
  
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
