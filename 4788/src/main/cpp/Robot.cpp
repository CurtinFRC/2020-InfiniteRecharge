#include "Robot.h"

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {
  lastTimestamp = Timer::GetFPGATimestamp();

  // Inverts one side of our drivetrain
  robotMap.driveSystem.LGearbox.transmission->SetInverted(true);
  robotMap.driveSystem.RGearbox.transmission->SetInverted(false);

  drivetrain->StartLoop(100); // WML Drivetrain


  // Registering our systems to be called
  StrategyController::Register(drivetrain);

  // Registering Systems to Network Tables
  NTProvider::Register(drivetrain);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {} 

void Robot::TestInit() {}
void Robot::TestPeriodic() {}