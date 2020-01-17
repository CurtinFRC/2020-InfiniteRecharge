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
  
  leftMotor1 = new TalonSrx(0);
  leftMotor2 = new TalonSrx(1);
  leftMotor1->SetInverted(false);
  leftMotor2->SetInverted(false);
  left = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*leftMotor1, *leftMotor2)), nullptr};

  rightMotor1 = new TalonSrx(2);
  rightMotor2 = new TalonSrx(3);
  rightMotor1->SetInverted(true);
  rightMotor2->SetInverted(true);
  right = new Gearbox{ new wml::actuators::MotorVoltageController(new SpeedControllerGroup(*rightMotor1, *rightMotor2)), nullptr};

  TurretRoation = new TalonSrx(4);
  TurretAngle = new TalonSrx(6);
  FlyWheel = new TalonSrx(5);

  AnalogInput *exampleAnalog = new AnalogInput(0);

  DrivetrainConfig drivetrainConfig{*left, *right};
  drivetrain = new Drivetrain(drivetrainConfig);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;

  double leftSpeed = -xbox1->GetAxisType(hand::kLeftHand); // L Y axis
  double rightSpeed = -xbox1->GetAxisType(hand::kRightHand); // R Y axis  

  leftSpeed *= fabs(leftSpeed);
  rightSpeed *= fabs(rightSpeed);

  if (xbox2->GetTriggerAxis(hand::kLeftHand) > 0.1) {
    FlyWheel->Set(xbox2->GetTriggerAxis(hand::kLeftHand));
  }

  if (xbox2->GetAxisType(hand::kRightHand) > 0.1) {
    TurretRoation->Set(xbox2->GetAxisType(hand::kRightHand));
  }

  if (xbox2->GetBumper(hand::kRightHand)) {
    solenoid.SetTarget(actuators::BinaryActuatorState::kForward);
  } else {
    solenoid.SetTarget(actuators::BinaryActuatorState::kReverse);
  }

  if (pressureSensor.GetScaled() < 80) {
    compressor.SetTarget(actuators::BinaryActuatorState::kForward);
  }

  drivetrain->Set(leftSpeed, rightSpeed);

  compressor.Update(dt);
  solenoid.Update(dt);

  compressor.Update(dt);
  solenoid.Update(dt);

  // Stop the solenoid if it's finished
  if (solenoid.IsDone()) solenoid.Stop();
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
