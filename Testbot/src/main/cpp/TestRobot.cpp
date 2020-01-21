#include "TestRobot.h"

#include "frc/AnalogInput.h"
#include <actuators/VoltageController.h>

#include <math.h>
#include <iostream>

using namespace frc;
using namespace wml;

double lastTimestamp;

using hand = frc::XboxController::JoystickHand;

void Robot::RobotInit() {

  // Get's last time stamp, used to calculate dt
  lastTimestamp = Timer::GetFPGATimestamp();

  xbox1 = new frc::XboxController(0);
  xbox2 = new frc::XboxController(1);
  
  leftMotor1 = new TalonSrx(4);
  leftMotor2 = new TalonSrx(1);
  leftMotor1->SetInverted(false);
  leftMotor2->SetInverted(false);
  left = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*leftMotor1, *leftMotor2)), nullptr};

  rightMotor1 = new TalonSrx(2);
  rightMotor2 = new TalonSrx(3);
  rightMotor1->SetInverted(true);
  rightMotor2->SetInverted(true);
  right = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*rightMotor1, *rightMotor2)), nullptr};

  TurretRoation = new TalonSrx(0);
  TurretAngle = new TalonSrx(6);
  FlyWheel = new TalonSrx(5);

  auto inst = nt::NetworkTableInstance::GetDefault();
	auto visionTable = inst.GetTable("VisionTracking");
	table = visionTable->GetSubTable("Target");

  TargetX = table->GetEntry("Target_X");
	TargetY = table->GetEntry("Target_Y");
	ImageHeight = table->GetEntry("ImageHeight");
	ImageWidth = table->GetEntry("ImageWidth");

  AnalogInput *exampleAnalog = new AnalogInput(0);

  DrivetrainConfig drivetrainConfig{*left, *right};
  drivetrain = new Drivetrain(drivetrainConfig);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;

  double imageHeight = table->GetNumber("ImageHeight", 0); 
	double imageWidth = table->GetNumber("ImageWidth", 0);

	double targetX = table->GetNumber("Target_X", 0)/imageWidth;
	double targetY = table->GetNumber("Target_Y", 0)/imageHeight;  

  double turretSpeed;

  double leftSpeed = -xbox1->GetAxisType(hand::kLeftHand); // L Y axis
  double rightSpeed = -xbox1->GetAxisType(hand::kRightHand); // R Y axis  

  // if (xbox1->GetAxisType(hand::kRightHand) > 0.1) {
  //   turretSpeed = xbox1->GetAxisType(hand::kRightHand);
  // }

  if (xbox1->GetTriggerAxis(hand::kLeftHand) > 0.1) {
    if (targetX > imageHeight || targetY > imageWidth) {
      std::cout << "Error: >> Vision Artifacting Detected" << std::endl; 
    } else {
      turretSpeed = PIDCalc(dt, targetX);
      std::cout << "Turret Roation Speed" << turretSpeed << std::endl;
    }
  } 

  // drivetrain->Set(leftSpeed, rightSpeed);
  TurretRoation->Set(turretSpeed);

  compressor.Update(dt);
  solenoid.Update(dt);

  compressor.Update(dt);
  solenoid.Update(dt);

  // Stop the solenoid if it's finished
  if (solenoid.IsDone()) solenoid.Stop();
}

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
