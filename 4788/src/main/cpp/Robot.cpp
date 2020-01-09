#include "Robot.h"

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {
  // Get's last time stamp, used to calculate dt
  lastTimestamp = Timer::GetFPGATimestamp();

  // Initializes The smart controllers assigned in robotmap
  ControlMap::InitSmartControllerGroup(robotMap.contGroup);

  // --------------------------Drivetrain--------------------------

  // Inverts one side of our drivetrain
  robotMap.driveSystem.LGearbox.transmission->SetInverted(true);
  robotMap.driveSystem.RGearbox.transmission->SetInverted(false);

  // Initializes drivetrain
  drivetrain = new Drivetrain(robotMap.driveSystem.driveTrainConfig, robotMap.driveSystem.gainsVelocity);
  drivetrain->StartLoop(100);


  // Registering our systems to be called
  StrategyController::Register(drivetrain);

  // Registering Systems to Network Tables
  NTProvider::Register(drivetrain);
}

void Robot::RobotPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {} 

void Robot::TestInit() {}
void Robot::TestPeriodic() {}