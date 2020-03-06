#include "Robot.h"

using namespace frc;
using namespace wml;

double CurrentTime;
double lastTimestamp;
double dt;

StrategyBuilder builder;

void Robot::RobotInit() {

  // Initializes The smart controllers assigned in robotmap
  ControlMap::InitSmartControllerGroup(robotMap.contGroup);

  // auto cameraFront = CameraServer::GetInstance()->StartAutomaticCapture(0);
  // auto cameraBack = CameraServer::GetInstance()->StartAutomaticCapture(1);

  // cameraFront.SetFPS(30);
  // cameraBack.SetFPS(30);

  // cameraFront.SetResolution(160, 120);
  // cameraBack.SetResolution(160, 120);

  // Initializers
  drivetrain = new Drivetrain(robotMap.driveSystem.driveTrainConfig, robotMap.driveSystem.gainsVelocity);
  wayFinder = new WayFinder(ControlMap::DriveKp, ControlMap::DriveKi, ControlMap::DriveKd, *drivetrain, ControlMap::AutoGearRatio, ControlMap::WheelDiameter);
  intake = new Intake(robotMap.intake.intakeMotor, robotMap.intake.IntakeDown);
  magLoader = new MagLoader(robotMap.magLoader.magLoaderMotor, robotMap.magLoader.StartMagSensor, robotMap.magLoader.IndexSensor, robotMap.magLoader.StopSensor);
  climber = new Climber(robotMap.climber.ClimberElevatorLeft, robotMap.climber.ClimberElevatorRight, robotMap.climber.ClimberActuator);
  turret = new Turret(robotMap.turret.turretRotation, robotMap.turret.turretAngle, robotMap.turret.turretFlyWheel, robotMap.turret.LeftLimit, robotMap.turret.AngleDownLimit);

  // Zero All Encoders
  robotMap.driveSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  robotMap.driveSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();

  // Strategy controllers
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain,  robotMap.driveSystem.ChangeGearing, robotMap.driveSystem.Shift2PTO, robotMap.driveSystem.PTORatchetLeft, robotMap.driveSystem.PTORatchetRight, robotMap.contGroup));
  drivetrain->StartLoop(100);

  intake->SetDefault(std::make_shared<IntakeManualStrategy>(*intake, robotMap.contGroup));
  magLoader->SetDefault(std::make_shared<MagLoaderManualStrategy>(*magLoader, robotMap.contGroup));
  climber->SetDefault(std::make_shared<ClimberManualStrategy>(*climber, robotMap.contGroup));
  turret->SetDefault(std::make_shared<TurretManualStrategy>(*turret, robotMap.contGroup));

  // Inverts one side of our drivetrain
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(false);

  // Network tables
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Autonomous");
  auto activeTable = inst.GetTable("Activity");

  AutoSelector = table->GetEntry("AutoSelector");
  RobotActive = activeTable->GetEntry("ActiveRobot");

  // Registering our systems to be called via strategy
  StrategyController::Register(drivetrain);
  StrategyController::Register(intake);
  StrategyController::Register(magLoader);
  StrategyController::Register(climber);
  StrategyController::Register(turret);

  NTProvider::Register(drivetrain); // Registers system to networktables
}

void Robot::RobotPeriodic() {
  CurrentTime = frc::Timer::GetFPGATimestamp();
  dt = CurrentTime - lastTimestamp;

  robotMap.autonomous.AutoSelecter = AutoSelector.GetDouble(1);
  RobotActive.SetBoolean(true);
  
  StrategyController::Update(dt);
  intake->Update(dt);
  magLoader->Update(dt);
  climber->Update(dt);
  turret->Update(dt);
  NTProvider::Update();

  std::cout << "Rotation Sensor: " << robotMap.turret.LeftLimit.Get() << std::endl;

  // //std::cout << "TurretAngle: " << robotMap.turret.turretAngle.encoder->GetEncoderRotations() << std::endl;
  std::cout << "TurretRotation: " << robotMap.turret.turretRotation.encoder->GetEncoderRotations() << std::endl;
  // //std::cout << "TurretFlyWheel: " << robotMap.turret.turretFlyWheel.encoder->GetEncoderAngularVelocity() << std::endl;

  // std::cout << "Flywheel encoder: " << robotMap.turret.flywheelEncoder.GetEncoderAngularVelocity() << std::endl;
  // std::cout << "Angle encoder" << robotMap.turret.angleEncoder.GetEncoderRotations() << std::endl;

  lastTimestamp = CurrentTime;
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

// Code called once when auto starts
void Robot::AutonomousInit() {
}

// Auto loops
void Robot::AutonomousPeriodic() {

}

// Start of teleop
void Robot::TeleopInit() { 
  Schedule(drivetrain->GetDefaultStrategy(), true);
  Schedule(intake->GetDefaultStrategy(), true);
  Schedule(magLoader->GetDefaultStrategy(), true);
  Schedule(climber->GetDefaultStrategy(), true);
}

// Teleop Loops
void Robot::TeleopPeriodic() {}


// Start of test
void Robot::TestInit() {
  Schedule(std::make_shared<DrivetrainTest>(*drivetrain, wml::control::PIDGains{ "I am gains 2: Electric Boogaloo", 1, 0, 0 }));
}

// Test loops
void Robot::TestPeriodic() {}
