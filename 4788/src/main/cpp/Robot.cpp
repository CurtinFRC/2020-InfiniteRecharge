#include "Robot.h"

// Robot.cpp is our main entrypoint

using hand = frc::XboxController::JoystickHand;

double lastTimestamp;

// Variables to store our wanted speed for each side
double leftSpeed;
double rightSpeed;

double dt; //dt stands for delta time

void Robot::RobotInit() {

  dt = frc::Timer::GetFPGATimestamp() - lastTimestamp;
  lastTimestamp = frc::Timer::GetFPGATimestamp();
  // use the provided timers to calculate the time since the last cycle was run
  
  NTProvider::Register(&pressureSensor);  // Register the pressure sensor as a sensor to be logged to NetworkTables

  // controllers
  xbox = new frc::XboxController(0);
  
  // Drivebase
  leftMotor[0] = new frc::Spark(0);
  rightMotor[0] = new frc::Spark(1);

  leftMotor[0]->SetInverted(true);
  rightMotor[0]->SetInverted(false);

  // Hammer
  hammer[0] = new frc::Spark(2);

}

void Robot::RobotPeriodic() {
  if (pressureSensor.GetScaled() < 80) {                            // If the pressure drops below 80 psi...
    compressor.SetTarget(wml::actuators::BinaryActuatorState::kForward); // ... turn the compressor on.
  }
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {


  // Drivebase
  leftSpeed = xbox->GetY(hand::kLeftHand);
  leftSpeed = xbox->GetY(hand::kRightHand);

  leftMotor[0]->Set(leftSpeed);
  rightMotor[0]->Set(rightSpeed);

  // Hammer
  if (xbox->GetAButton()) {
    hammer[0]->Set(0.5);
  } else if (xbox->GetBButton()) {
    hammer[0]->Set(-0.5);
  } else {
    hammer[0]->Set(0);
  }

  // Pneumatics
  if (xbox->GetXButton()) {
    solenoid.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  } else {
    solenoid.SetTarget(wml::actuators::BinaryActuatorState::kReverse); // if reverse doesn't work use forward. Might be toggle
  }

  // The update methods need to be called every cycle for the actuators to actualy do anything
  compressor.Update(dt);
  solenoid.Update(dt);

  // Stop the solenoid if it's finished
  if (solenoid.IsDone()) solenoid.Stop();

  NTProvider::Update();     // Updates values sent to NetworkTables
} 

void Robot::TestInit() {}
void Robot::TestPeriodic() {}