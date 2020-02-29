#include "Robot.h"

using namespace frc;
using namespace wml;

double CurrentTime;
double lastTimestamp;
double dt;

void Robot::RobotInit() {

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

  // Turret FATBOI... ffs, not again
  turret = new Turret(robotMap.turret.turretRotation, 
                      robotMap.turret.turretAngle, 
                      robotMap.turret.turretFlyWheel, 
                      robotMap.turret.LeftLimit, 
                      robotMap.turret.RightLimit, 
                      robotMap.turret.AngleDownLimit, 
                      robotMap.contGroup, 
                      robotMap.controlSystem.visionTable, 
                      robotMap.controlSystem.rotationTable, 
                      robotMap.controlSystem.FlyWheelToggle,
                      robotMap.controlSystem.TurretToggle, 
                      robotMap.autonomous.AutoSelecter, 
                      robotMap.autonomous.StartDoComplete, 
                      robotMap.autonomous.StartPointComplete, 
                      robotMap.autonomous.WayPoint1Complete, 
                      robotMap.autonomous.WayPoint2Complete, 
                      robotMap.autonomous.WayPoint3Complete, 
                      robotMap.autonomous.EndComplete);

  magLoader = new MagLoader(robotMap.magLoader.magLoaderMotor, robotMap.magLoader.StartMagLimit,robotMap.magLoader.Position1Limit, robotMap.magLoader.Position5Limit, robotMap.contGroup);
  beltIntake = new BeltIntake(robotMap.intake.intakeMotor, robotMap.intake.IntakeDown, robotMap.contGroup, robotMap.autonomous.AutoSelecter, robotMap.autonomous.StartDoComplete, robotMap.autonomous.StartPointComplete, robotMap.autonomous.WayPoint1Complete, robotMap.autonomous.WayPoint2Complete, robotMap.autonomous.WayPoint3Complete, robotMap.autonomous.EndComplete, robotMap.controlSystem.FlyWheelToggle, robotMap.controlSystem.TurretToggle);
  climber = new Climber(robotMap.climber.ClimberActuator, robotMap.intake.IntakeDown, robotMap.climber.ClimberElevatorLeft, robotMap.climber.ClimberElevatorRight, robotMap.contGroup, robotMap.controlSystem.TurretToggle);
  controlPannel = new ControlPannel(robotMap.controlPannel.ControlPannelMotor, robotMap.controlPannel.ExtendControlPannelMotor, robotMap.contGroup);

  // WayFinder (fake pathfinder basically)
  wayFinder = new WayFinder(ControlMap::DriveKp, ControlMap::DriveKi, ControlMap::DriveKd, *drivetrain, ControlMap::AutoGearRatio, ControlMap::WheelDiameter);

  // Zero All Encoders
  robotMap.driveSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  robotMap.driveSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();

  // Strategy controllers
  drivetrain->SetDefault(std::make_shared<DrivetrainManual>("Drivetrain Manual", *drivetrain,  robotMap.driveSystem.ChangeGearing, robotMap.driveSystem.Shift2PTO, robotMap.driveSystem.PTORatchetLeft, robotMap.driveSystem.PTORatchetRight, robotMap.contGroup));
  drivetrain->StartLoop(100);

  // Inverts one side of our drivetrain
  drivetrain->GetConfig().rightDrive.transmission->SetInverted(true);
  drivetrain->GetConfig().leftDrive.transmission->SetInverted(false);

  // Inverts Turret Motors
  robotMap.turret.turretFlyWheel.transmission->SetInverted(true);
  robotMap.turret.turretRotation.transmission->SetInverted(true);

  // Inverts Intake Motors
  robotMap.intake.intakeMotor.transmission->SetInverted(false);

  // Inverts Mag Motors
  robotMap.magLoader.magLoaderMotor.transmission->SetInverted(false);

  // Arduino Controller
  robotMap.controlSystem.arduino.WriteBulk(&robotMap.controlSystem.message, 16);
  robotMap.controlSystem.message = 78;

  turret->InitializeSetPoints();

  // Network tables
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Autonomous");
  auto activeTable = inst.GetTable("Activity");

  AutoSelector = table->GetEntry("AutoSelector");
  RobotActive = activeTable->GetEntry("ActiveRobot");

  // Registering our systems to be called via strategy
  StrategyController::Register(drivetrain);
  NTProvider::Register(drivetrain); // Registers system to networktables
}

void Robot::RobotPeriodic() {
  CurrentTime = frc::Timer::GetFPGATimestamp();
  dt = CurrentTime - lastTimestamp;

  robotMap.autonomous.AutoSelecter = AutoSelector.GetDouble(1);
  RobotActive.SetBoolean(true);
  
  // std::cout << "Angle: " << robotMap.driveSystem.drivetrain.GetConfig().gyro->GetAngle() << std::endl;
  // std::cout << "Encoder Left: " << robotMap.driveSystem.drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() << std::endl;
  // std::cout << "Encoder Right: " << robotMap.driveSystem.drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() << std::endl;

  // std::cout << "Sensor1: " << robotMap.magLoader.StartMagLimit.GetAverageValue() << std::endl;
  // std::cout << "Sensor2: " << robotMap.magLoader.Position5Limit.GetAverageValue() << std::endl;
  // std::cout << "Sensor3: " << robotMap.magLoader.Position5Limit.GetAverageValue() << std::endl;

  // std::cout << "TurretAngle: " << robotMap.turret.turretAngle.encoder->GetEncoderRotations() << std::endl;
  // std::cout << "TurretRotation: " << robotMap.turret.turretRotation.encoder->GetEncoderRotations() << std::endl;
  std::cout << "TurretFlyWheel: " << robotMap.turret.turretFlyWheel.encoder->GetEncoderAngularVelocity() << std::endl;

  // std::cout << "Motor1: " << robotMap.turret.TurretFlyWheel.GetVoltage() << std::endl;
  // std::cout << "Motor2: " << robotMap.turret.TurretFlyWheel2.GetVoltage() << std::endl;

  // robotMap.controlSystem.compressor.SetTarget(wml::actuators::BinaryActuatorState::kForward);
  // robotMap.controlSystem.compressor.Update(dt);
  StrategyController::Update(dt);
  NTProvider::Update();

  lastTimestamp = CurrentTime;
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

// Code called once when auto starts
void Robot::AutonomousInit() {
  Schedule(std::make_shared<DrivetrainAuto>(*drivetrain, 
                                            *wayFinder,
                                            wml::control::PIDGains{ "I am gains", 1, 0, 0 }, 
                                            robotMap.driveSystem.ChangeGearing,
                                            robotMap.driveSystem.Shift2PTO,
                                            robotMap.autonomous.AutoSelecter, 
                                            robotMap.autonomous.StartDoComplete,
                                            robotMap.autonomous.StartPointComplete, 
                                            robotMap.autonomous.WayPoint1Complete, 
                                            robotMap.autonomous.WayPoint2Complete, 
                                            robotMap.autonomous.WayPoint3Complete, 
                                            robotMap.autonomous.EndComplete));
  // Zero Robot For Autonomous
  // turret->ZeroTurret();
  robotMap.driveSystem.drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  robotMap.driveSystem.drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  robotMap.driveSystem.drivetrain.GetConfig().gyro->Reset();
}

// Auto loops
void Robot::AutonomousPeriodic() {
  turret->AutoOnUpdate(dt);
  magLoader->AutoOnUpdate(dt);
  beltIntake->AutoOnUpdate(dt);
}

// Start of teleop
void Robot::TeleopInit() { 
  Schedule(drivetrain->GetDefaultStrategy(), true);
  // turret->ZeroTurret();
}

// Teleop Loops
void Robot::TeleopPeriodic() {
  turret->TeleopOnUpdate(dt);
  magLoader->TeleopOnUpdate(dt);
  beltIntake->TeleopOnUpdate(dt);
  climber->TeleopOnUpdate(dt);
  controlPannel->TeleopOnUpdate(dt);
}


// Start of test
void Robot::TestInit() {
  Schedule(std::make_shared<DrivetrainTest>(*drivetrain, wml::control::PIDGains{ "I am gains 2: Electric Boogaloo", 1, 0, 0 }));
}

// Test loops
void Robot::TestPeriodic() {
  turret->TestOnUpdate(dt);
  magLoader->TestOnUpdate(dt);
  beltIntake->TestOnUpdate(dt);
  climber->TestOnUpdate(dt);
  controlPannel->TestOnUpdate(dt);
}
