#include "Robot.h"

using namespace frc;
using namespace wml;

double lastTimestamp;
double dt;

void Robot::RobotInit() {
  // Get's last time stamp, used to calculate dt
  lastTimestamp = Timer::GetFPGATimestamp();

  // Initializes The smart controllers assigned in robotmap
  ControlMap::InitSmartControllerGroup(robotMap.contGroup);

  // --------------------------Drivetrain--------------------------

  // Initializers
  drivetrain = new Drivetrain(robotMap.driveSystem.driveTrainConfig, robotMap.driveSystem.gainsVelocity);
  turret = new Turret(robotMap.turret.turretRotation, robotMap.turret.turretAngle, robotMap.turret.turretFlyWheel, robotMap.contGroup);
  magLoader = new MagLoader(robotMap.magLoader.magLoaderMotor, robotMap.contGroup);


  // Strategy controllers
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain, robotMap.contGroup));
  drivetrain->StartLoop(100);

  // Inverts one side of our drivetrain
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);

  // Registering our systems to be called
  StrategyController::Register(drivetrain);
  NTProvider::Register(drivetrain); // Registers system to networktables
}

void Robot::RobotPeriodic() {
  dt = Timer::GetFPGATimestamp() - lastTimestamp;

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

void Robot::TeleopInit() { 
  Schedule(drivetrain->GetDefaultStrategy(), true);
}
void Robot::TeleopPeriodic() {
  turret->TeleopOnUpdate(dt);
  magLoader->TeleopOnUpdate(dt);
}

void Robot::TestInit() {
  Schedule(std::make_shared<DrivetrainTest>(*drivetrain, wml::control::PIDGains{ "I am gains 2: Elecis Booglsesoo", 1, 0, 0 }));
}
void Robot::TestPeriodic() {}