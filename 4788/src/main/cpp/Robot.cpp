#include "Robot.h"

// Robot.cpp is our main entrypoint

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {
  lastTimestamp = Timer::GetFPGATimestamp();
  
  robotMap.driveSystem.LGearbox.transmission->SetInverted(true);
  robotMap.driveSystem.RGearbox.transmission->SetInverted(false);

  drivetrain->StartLoop(100);

  StrategyController::Register(drivetrain);
  StrategyController::Register(subSystem1);
  StrategyController::Register(subSystem2);

  // For ShuffleBoard
  NTProvider::Register(drivetrain);
  NTProvider::Register(subSystem1);
  NTProvider::Register(subSystem2);
  NTProvider::Register(&robotMap.controlSystem.pressorSensor);

  // long and complicated way of saying on
  robotMap.controlSystem.compressor.SetTarget(actuators::BinaryActuatorState::kForward);
  std::cout << "Robot SetUp Complete" << std::endl;
}

void Robot::RobotPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;
  lastTimestamp = Timer::GetFPGATimestamp();
  
  StrategyController::Update(dt);
  NTProvider::Update();
  robotMap.controlSystem.compressor.Update(dt);
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