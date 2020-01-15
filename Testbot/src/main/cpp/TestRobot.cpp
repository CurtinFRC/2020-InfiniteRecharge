#include "TestRobot.h"

#include <actuators/VoltageController.h>

#include <math.h>
#include <iostream>

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {

  // Get's last time stamp, used to calculate dt
  lastTimestamp = Timer::GetFPGATimestamp();

  xbox = new wml::controllers::XboxController(0);
  
  leftMotors = new TalonSrx(2);
  leftMotors->SetInverted(false);
  //left = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*leftMotors)), nullptr};

  rightMotors= new TalonSrx(5);
  rightMotors->SetInverted(true);
  //right = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*rightMotors)), nullptr};

  bagMotor = new VictorSpx(8);
  hatchEjector = new DoubleSolenoid(0, 1);

  DrivetrainConfig drivetrainConfig{*left, *right};
  drivetrain = new Drivetrain(drivetrainConfig);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;

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

  leftSpeed = PIDCalc(dt, Xoffset);
  rightSpeed = -PIDCalc(dt, Xoffset);

  // leftSpeed *= fabs(leftSpeed);
  // rightSpeed *= fabs(rightSpeed);

  leftMotors->Set(leftSpeed);
  rightMotors->Set(rightSpeed);

  //bagMotor->Set(100);



  drivetrain->Set(leftSpeed, rightSpeed);

  hatchEjector->Set(!xbox->GetButton(6) ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse); // R bumper
  
}

double kP = -0.8;
double kI = 0;
double kD = -0.005;

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
