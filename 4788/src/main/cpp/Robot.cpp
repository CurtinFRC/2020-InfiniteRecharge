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

  // Initializes drivetrain
  drivetrain = new Drivetrain(robotMap.driveSystem.driveTrainConfig, robotMap.driveSystem.gainsVelocity);
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain, robotMap.contGroup));
  drivetrain->StartLoop(100);

  // Inverts one side of our drivetrain
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);

  // ----------------------------Turret----------------------------
  //@TODO


  // Registering our systems to be called
  StrategyController::Register(drivetrain);

  // Registering Systems to Network Tables
  NTProvider::Register(drivetrain);
}

void Robot::RobotPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;

  StrategyController::Update(dt);
  NTProvider::Update();
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {
  Schedule(std::make_shared<DrivetrainAuto>(*drivetrain, wml::control::PIDGains{ "I am gains", 1, 0, 0 }));
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() { Schedule(drivetrain->GetDefaultStrategy(), true); }
void Robot::TeleopPeriodic() {
  
}

void Robot::TestInit() {
  Schedule(std::make_shared<DrivetrainTest>(*drivetrain, wml::control::PIDGains{ "I am gains 2: Elecis Booglsesoo", 1, 0, 0 }));
}
void Robot::TestPeriodic() {}