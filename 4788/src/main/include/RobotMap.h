#pragma once

#include <string>
#include <stdint.h>

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

// WML
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
#include "wayfinder.h"


struct RobotMap {

  // Controllers
  #if __CONTROLMAP_USING_JOYSTICK__
  
  wml::controllers::Joystick joy1{ ControlMap::JoyController1Port };
  wml::controllers::Joystick joy2{ ControlMap::JoyController2Port };
  wml::controllers::Joystick override{ ControlMap::JoyController3Port};
  wml::controllers::SmartControllerGroup contGroup{ joy1, joy2, override };
  #else

  wml::controllers::XboxController xbox1{ ControlMap::XboxController1Port };
  wml::controllers::XboxController xbox2{ ControlMap::XboxController2Port };
  wml::controllers::Joystick override{ ControlMap::JoyController3Port};
  wml::controllers::SmartControllerGroup contGroup{ xbox1, xbox2, override};
  #endif

  // Drive System
  struct DriveSystem {
    // Front
    wml::SparkMax FLmax{ ControlMap::DriveMAXportFL, wml::SparkMax::MotorType::kNEO, 42 };
    wml::SparkMax FRmax{ ControlMap::DriveMAXportFR, wml::SparkMax::MotorType::kNEO, 42 };

    // Back
    wml::SparkMax BLmax{ ControlMap::DriveMAXportBL, wml::SparkMax::MotorType::kNEO, 42 };
    wml::SparkMax BRmax{ ControlMap::DriveMAXportBR, wml::SparkMax::MotorType::kNEO, 42 };


    wml::actuators::MotorVoltageController leftMotors = wml::actuators::MotorVoltageController::Group(FLmax, BLmax);
    wml::actuators::MotorVoltageController rightMotors = wml::actuators::MotorVoltageController::Group(FRmax, BRmax);

    wml::Gearbox LGearbox{ &leftMotors, &FLmax, 8.45 };
    wml::Gearbox RGearbox{ &rightMotors, &FRmax, 8.45 };

    wml::actuators::DoubleSolenoid ChangeGearing{ ControlMap::PCModule, ControlMap::ChangeGearPort1, ControlMap::ChangeGearPort2, ControlMap::ChangeGearTime };
    wml::actuators::DoubleSolenoid Shift2PTO{ ControlMap::PCModule, ControlMap::Shift2PTOPort1, ControlMap::Shift2PTOPort2, ControlMap::ShiftPTOActuationTime };

    wml::sensors::NavX navx{};
    wml::sensors::NavXGyro gyro{ navx.Angular(wml::sensors::AngularAxis::YAW) };
    wml::sensors::NavXGyro gyro1{ navx.Angular(wml::sensors::AngularAxis::PITCH) };
    wml::sensors::NavXGyro gyro2{ navx.Angular(wml::sensors::AngularAxis::ROLL) };

    wml::DrivetrainConfig driveTrainConfig{ LGearbox, RGearbox, &gyro, 0.56, 0.60, 0.0762, 50 };
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
    wml::TalonSrx TurretFlyWheel{ ControlMap::TurretFlyWheelPort, 2048 };
    wml::TalonSrx TurretFlyWheel2{ ControlMap::TurretFlyWheelPort2, 2048 };
    wml::actuators::MotorVoltageController flywheelMotors = wml::actuators::MotorVoltageController::Group(TurretFlyWheel, TurretFlyWheel2);
    wml::Gearbox turretFlyWheel{ &flywheelMotors, &TurretFlyWheel, 8.45 };
  };
  Turret turret;

  struct Intake {
    wml::TalonSrx IntakeMotor{ ControlMap::IntakeMotorPort, 2048 };
    wml::actuators::DoubleSolenoid IntakeDown { ControlMap::PCModule, ControlMap::IntakeDownPort1, ControlMap::IntakeDownPort2 , ControlMap::PannelActuationTime};
    wml::actuators::MotorVoltageController IntakeMotors = wml::actuators::MotorVoltageController::Group(IntakeMotor);
    wml::Gearbox intakeMotor{ &IntakeMotors, &IntakeMotor, 8.45};
    
  };
  Intake intake;

  struct MagLoader {
    frc::AnalogInput StartMagLimit{ ControlMap::StartMagLimitPort };
    frc::AnalogInput Position1Limit{ ControlMap::Position1LimitPort };
    frc::AnalogInput Position5Limit{ ControlMap::Position5LimitPort };

    wml::TalonSrx MagLoaderMotor{ ControlMap::MagLoaderMotorPort, 2048 };
    wml::actuators::MotorVoltageController magLoaderMotors = wml::actuators::MotorVoltageController::Group(MagLoaderMotor);
    wml::Gearbox magLoaderMotor{ &magLoaderMotors, &MagLoaderMotor, 8.45 };
  };
  MagLoader magLoader;

  struct ControlPannel {
    wml::TalonSrx MotorControlPannel{ ControlMap::ControlPannelPort };
    wml::TalonSrx ExtendControlPannel{ ControlMap::ControlPannelUpPort };

    wml::Gearbox ControlPannelMotor { new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(MotorControlPannel)), nullptr };
    wml::Gearbox ExtendControlPannelMotor { new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(ExtendControlPannel)), nullptr };
  };
   ControlPannel controlPannel;

  struct Climber {
    wml::actuators::DoubleSolenoid ClimberActuator{ ControlMap::PCModule, ControlMap::ClimberActuatorPort1, ControlMap::ClimberActuatorPort2, ControlMap::ClimberActuationTime };

    wml::TalonSrx Climber2Motor{ ControlMap::ClimberMotor2Port, 2048};
    wml::actuators::MotorVoltageController Climber2Motors = wml::actuators::MotorVoltageController::Group(Climber2Motor);
    wml::Gearbox ClimberElevatorLeft{ &Climber2Motors, &Climber2Motor, 8.45};

    wml::TalonSrx Climber1Motor{ ControlMap::ClimberMotor1Port, 2048};
    wml::actuators::MotorVoltageController Climber1Motors  = wml::actuators::MotorVoltageController::Group(Climber1Motor);
    wml::Gearbox ClimberElevatorRight{ &Climber1Motors, &Climber1Motor, 8.45};
  };
  Climber climber;

  struct Auto {

    /**
     * Auto Selection
     * 8 Ball = 1 (Default)
     * 6 Ball = 2
     * 3 Ball Left = 3
     * 3 Ball Mid = 4
     * 3 Ball Right = 5
    */ 

    // Selection
    int AutoSelecter = 1;

    // Public booleans for subsystems
    bool StartDoComplete = true;
    bool StartPointComplete = false;
    bool WayPoint1Complete = false;
    bool WayPoint2Complete = false;
    bool WayPoint3Complete = false;
    bool EndComplete = false;
  };
  Auto autonomous;

  struct ControlSystem {

    // Pneumatics
    wml::sensors::PressureSensor pressureSensor{ ControlMap::PressureSensorPort };
    wml::actuators::Compressor compressor{ ControlMap::CompressorPort }; 

    // Vision
    std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking");

    // Extra Controller
    frc::I2C arduino{ frc::I2C::kOnboard, 8 };
    uint8_t message = 73;
    // Climber

    //Turret
    std::shared_ptr<nt::NetworkTable> rotationTable = nt::NetworkTableInstance::GetDefault().GetTable("Sharing values");

    
    bool TurretToggle = false;
    bool FlyWheelToggle = false;
  };
  ControlSystem controlSystem;
};