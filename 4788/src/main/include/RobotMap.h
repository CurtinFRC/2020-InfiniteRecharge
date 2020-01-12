#pragma once

#include "devices/StateDevice.h"
#include "control/PIDController.h"
#include "strategy/StrategySystem.h"
#include "control/MotorFilters.h"
#include "Gearbox.h"
#include "strategy/Strategy.h"
#include "controllers/Controllers.h"
#include "sensors/BinarySensor.h"

#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>

#include "WMLCtre.h"
#include "controllers/Controllers.h"
#include "Gearbox.h"
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
    wml::TalonSrx Lsrx{ ControlMap::DriveSRXportL };
    wml::TalonSrx Rsrx{ ControlMap::DriveSRXportR };
    wml::VictorSpx Lspx{ ControlMap::DriveSPXportL };
    wml::VictorSpx Rspx{ ControlMap::DriveSPXportR };

    // @TODO: Add encoders to drivetrain gearboxes (Will do when we have neo's... or if we have neo's... they may be on fire by the time they get here. Whatever)

    wml::Gearbox LGearbox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Lsrx, Lspx)), nullptr };
    wml::Gearbox RGearbox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Rsrx, Rspx)), nullptr };

    wml::DrivetrainConfig driveTrainConfig{ LGearbox, RGearbox };
    wml::Drivetrain drivetrain{ driveTrainConfig };
    wml::control::PIDGains gainsVelocity{ "Drivetrain Velocity", 1 };
  };
  DriveSystem driveSystem;


  struct ControlSystem {
    wml::sensors::PressureSensor pressureSensor{ ControlMap::PressureSensorPort };
    wml::actuators::Compressor compressor{ ControlMap::CompressorPort }; 

    // Vision Tracking Values Sent from the coprocessor (pi/tinkerboard)
    std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("VisionTracking");
    std::shared_ptr<nt::NetworkTable> table = visionTable->GetSubTable("Target");
    nt::NetworkTableEntry TargetX = table->GetEntry("Target_X"), TargetY = table->GetEntry("Target_Y");
  };
  ControlSystem controlSystem;
};