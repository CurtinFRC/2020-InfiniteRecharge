#pragma once

#include <string>

#include "devices/StateDevice.h"
#include "control/PIDController.h"
#include "strategy/StrategySystem.h"
#include "control/MotorFilters.h"
#include "Gearbox.h"
#include "strategy/Strategy.h"
#include "controllers/Controllers.h"
#include "sensors/BinarySensor.h"

// FRC
#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/PWMSparkMax.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/AnalogInput.h>

#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <wpi/Path.h>
#include <wpi/SmallString.h>

// REV
#include "rev/CANSparkMax.h"


#include "WMLCtre.h"
#include "controllers/Controllers.h"
#include "actuators/BinaryServo.h"
#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"
#include "actuators/VoltageController.h"
#include "Drivetrain.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"
#include "sensors/PressureSensor.h"
#include <networktables/NetworkTableInstance.h>
#include "control/PIDController.h"
#include "MotionProfiling.h"
#include "Toggle.h"
#include "WMLRev.h"

#include "Usage.h"

// Local Files
#include "ControlMap.h"


struct RobotMap {

  // Controllers
  #if __CONTROLMAP_USING_JOYSTICK__
  
  wml::controllers::Joystick joy1{ ControlMap::JoyController1Port };
  wml::controllers::Joystick joy2{ ControlMap::JoyController2Port };
  wml::controllers::SmartControllerGroup contGroup{ joy1, joy2 };
  #else

  wml::controllers::XboxController xbox1{ ControlMap::XboxController1Port };
  wml::controllers::XboxController xbox2{ ControlMap::XboxController2Port };
  wml::controllers::SmartControllerGroup contGroup{ xbox1, xbox2 };
  #endif

  // Drive System
  struct DriveSystem {
    // Front
    // wml::SparkMax FLmax{ ControlMap::DriveMAXportFL, wml::SparkMax::MotorType::kNEO, 2048 };
    // wml::SparkMax FRmax{ ControlMap::DriveMAXportFR, wml::SparkMax::MotorType::kNEO, 2048 };

    rev::CANSparkMax FLmax{ ControlMap::DriveMAXportFL, rev::CANSparkMax::MotorType::kBrushless };
    rev::CANSparkMax FRmax{ ControlMap::DriveMAXportFR, rev::CANSparkMax::MotorType::kBrushless };

    // Back
    // wml::SparkMax BLmax{ ControlMap::DriveMAXportBL, wml::SparkMax::MotorType::kNEO, 2048 };
    // wml::SparkMax BRmax{ ControlMap::DriveMAXportBR, wml::SparkMax::MotorType::kNEO, 2048 };

    rev::CANSparkMax BLmax{ ControlMap::DriveMAXportBL, rev::CANSparkMax::MotorType::kBrushless };
    rev::CANSparkMax BRmax{ ControlMap::DriveMAXportBR, rev::CANSparkMax::MotorType::kBrushless };

    // @TODO: Add encoders to drivetrain gearboxes (Will do when we have neo's... or if we have neo's... they may be on fire by the time they get here. Whatever)

    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(FLmax, BLmax);
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(FRmax, BRmax);

    wml::Gearbox LGearbox{ &leftMotors, nullptr/*&FLmax, 8.45*/ };
    wml::Gearbox RGearbox{ &rightMotors, nullptr/*&FRmax, 8.45*/ };

    wml::actuators::DoubleSolenoid ChangeGearing{ ControlMap::ChangeGearPort1, ControlMap::ChangeGearPort2, ControlMap::ChangeGearTime };

    wml::DrivetrainConfig driveTrainConfig{ LGearbox, RGearbox };
    wml::Drivetrain drivetrain{ driveTrainConfig };
    wml::control::PIDGains gainsVelocity{ "Drivetrain Velocity", 1 };
  };
  DriveSystem driveSystem;

  struct Turret {
    wml::sensors::LimitSwitch LeftLimit{ ControlMap::TurretLeftLimitPort, ControlMap::TurretLeftLimitInvert };
    wml::sensors::LimitSwitch RightLimit{ ControlMap::TurretRightLimitPort, ControlMap::TurretRightLimitInvert };
    wml::sensors::LimitSwitch AngleDownLimit{ ControlMap::TurretAngleDownLimitPort, ControlMap::TurretAngleDownLimitInvert };
    

    // Rotation
    wml::TalonSrx TurretRotation{ ControlMap::TurretRotationPort, 2048 };
    wml::actuators::MotorVoltageController rotationMotors = wml::actuators::MotorVoltageController::Group(TurretRotation);
    wml::Gearbox turretRotation{ &rotationMotors, &TurretRotation, 8.45 };

    // Angle
    wml::TalonSrx TurretAngle{ ControlMap::TurretAnglePort, 2048 };
    wml::actuators::MotorVoltageController turretAngleMotors = wml::actuators::MotorVoltageController::Group(TurretAngle);
    wml::Gearbox turretAngle{ &turretAngleMotors, &TurretAngle, 8.45 };

    // Fly Wheel
   // wml::TalonSrx TurretFlyWheel{ ControlMap::TurretFlyWheelPort, 2048 };
   // wml::actuators::MotorVoltageController flywheelMotors = wml::actuators::MotorVoltageController::Group(TurretFlyWheel);
   // wml::Gearbox turretFlyWheel{ &flywheelMotors, &TurretFlyWheel, 8.45 };


    rev::CANSparkMax TurretFlyWheel{ 4, rev::CANSparkMax::MotorType::kBrushed };
    rev::CANSparkMax TurretFlyWheel2{ 1, rev::CANSparkMax::MotorType::kBrushed };

    // wml::Gearbox turretFlyWheel{ TurretFlyWheel, nullptr};
    wml::Gearbox turretFlyWheel{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(TurretFlyWheel, TurretFlyWheel2)), nullptr };
    //wml::actuators::MotorVoltageController flywheelMotors = wml::actuators::MotorVoltageController::Group(TurretFlyWheel);
    
  };
  Turret turret;

  struct Intake {
    wml::TalonSrx IntakeMotor{ ControlMap::IntakeMotorPort, 2048 };
    wml::actuators::DoubleSolenoid IntakeDown { ControlMap::IntakeDownPort1, ControlMap::IntakeDownPort2 , ControlMap::PannelActuationTime};
    wml::actuators::MotorVoltageController IntakeMotors = wml::actuators::MotorVoltageController::Group(IntakeMotor);
    wml::Gearbox intakeMotor{ &IntakeMotors, &IntakeMotor, 8.45};
    
  };
  Intake intake;

  struct MagLoader {
    wml::sensors::LimitSwitch StartMagLimit{ ControlMap::StartMagLimitPort };
    wml::sensors::LimitSwitch Position1Limit{ ControlMap::Position1LimitPort };
    wml::sensors::LimitSwitch Position5Limit{ ControlMap::Position5LimitPort };

    frc::AnalogInput IRSensor{ 3 };

    wml::TalonSrx MagLoaderMotor{ ControlMap::MagLoaderMotorPort, 2048 };
    wml::actuators::MotorVoltageController magLoaderMotors = wml::actuators::MotorVoltageController::Group(MagLoaderMotor);
    wml::Gearbox magLoaderMotor{ &magLoaderMotors, &MagLoaderMotor, 8.45 };
  };
  MagLoader magLoader;

  struct ControlPannel {
    wml::TalonSrx MotorControlPannel{ ControlMap::ControlPannelPort };
    wml::actuators::DoubleSolenoid ControlPannelUpSol{ ControlMap::ControlPannelUpSolPort1, ControlMap::ControlPannelUpSolPort2, ControlMap::ControlPannelActuationTime};


    wml::Gearbox ControlPannelMotor { new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(MotorControlPannel)), nullptr };
   // wml::Gearbox ControlPannelUpSol { new wml::actuators::DoubleSolenoid(wml::actuators::DoubleSolenoid::Group(ControlPannelUpSol)), nullptr};
  };
  ControlPannel controlPannel;

  struct Climber {
    wml::actuators::DoubleSolenoid ClimberActuator{ ControlMap::ClimberActuatorPort1, ControlMap::ClimberActuatorPort2, ControlMap::ClimberActuationTime };

    wml::actuators::BinaryServo ShiftPTOServos{ ControlMap::Shift2PTOPort, ControlMap::Shift2PTOForwardPosition, ControlMap::Shift2PTOReversePosition };
    wml::TalonSrx Climber1Motor{ ControlMap::ClimberMotor1Port };
    wml::TalonSrx Climber2Motor{ ControlMap::ClimberMotor2Port };

    wml::Gearbox ClimberElevator{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Climber1Motor, Climber2Motor)), nullptr };
  };
  Climber climber;

  struct ControlSystem {

    // Pneumatics
    wml::sensors::PressureSensor pressureSensor{ ControlMap::PressureSensorPort };
    wml::actuators::Compressor compressor{ ControlMap::CompressorPort }; 

    // Vision
    std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking");

    // Auto
    wpi::SmallString<64> deployDirectory;
    // frc::filesystem::GetDeployDirectory(deployDirectory);

    //Belt intake 
   // std::shared_ptr<nt::NetworkTable> pancakes = nt::NetworkTableInstance::GetDefault().GetTable("Belt Intake Encoders");
  };
  ControlSystem controlSystem;


};