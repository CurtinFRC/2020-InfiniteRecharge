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

  auto cameraFront = CameraServer::GetInstance()->StartAutomaticCapture(0);
  auto cameraBack = CameraServer::GetInstance()->StartAutomaticCapture(1);

  cameraFront.SetFPS(30);
  cameraBack.SetFPS(30);

  cameraFront.SetResolution(160, 120);
  cameraBack.SetResolution(160, 120);

  // Initializers
  drivetrain = new Drivetrain(robotMap.driveSystem.driveTrainConfig, robotMap.driveSystem.gainsVelocity);
  turret = new Turret(robotMap.turret.turretRotation, robotMap.turret.turretAngle, robotMap.turret.turretFlyWheel, robotMap.turret.LeftLimit, robotMap.turret.RightLimit, robotMap.turret.AngleDownLimit, robotMap.contGroup, robotMap.controlSystem.visionTable);
  magLoader = new MagLoader(robotMap.magLoader.magLoaderMotor, robotMap.magLoader.StartMagLimit, robotMap.magLoader.Position1Limit, robotMap.magLoader.Position5Limit, robotMap.contGroup);
  beltIntake = new BeltIntake(robotMap.intake.intakeMotor, robotMap.intake.IntakeDown, robotMap.contGroup);
  climber = new Climber(robotMap.climber.ClimberActuator, robotMap.climber.ShiftPTOServos, robotMap.climber.ClimberElevator, robotMap.contGroup);
  controlPannel = new ControlPannel(robotMap.controlPannel.ControlPannelMotor, robotMap.controlPannel.PannelPnSol, robotMap.contGroup);

  // Strategy controllers
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain, robotMap.driveSystem.ChangeGearing, robotMap.contGroup));
  drivetrain->StartLoop(100);

  // Inverts one side of our drivetrain
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(false);

  // Registering our systems to be called via strategy
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
void Robot::AutonomousPeriodic() {
  turret->AutoOnUpdate(dt);
  magLoader->AutoOnUpdate(dt);
  beltIntake->AutoOnUpdate(dt);
  climber->AutoOnUpdate(dt);
}

void Robot::TeleopInit() { 
  Schedule(drivetrain->GetDefaultStrategy(), true);
  // turret->ZeroTurret();
}
void Robot::TeleopPeriodic() {
  turret->TeleopOnUpdate(dt);
  magLoader->TeleopOnUpdate(dt);
  beltIntake->TeleopOnUpdate(dt);
  climber->TeleopOnUpdate(dt);
 // std::cout << "Encoder Ticks" << robotMap.turret.TurretFlyWheel.GetEncoderTicks() << std::endl;
}

void Robot::TestInit() {
  Schedule(std::make_shared<DrivetrainTest>(*drivetrain, wml::control::PIDGains{ "I am gains 2: Electric Boogaloo", 1, 0, 0 }));
}
void Robot::TestPeriodic() {
  turret->TestOnUpdate(dt);
  magLoader->TestOnUpdate(dt);
  beltIntake->TestOnUpdate(dt);
  climber->TestOnUpdate(dt);
}