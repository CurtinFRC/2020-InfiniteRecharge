#pragma once

#include "ControlMap.h"

struct RobotMap {
  

  // Controllers
  #if __CONTROLMAP_USING_JOYSTICK__
  
  wml::controllers::Joystick joy1{ ControlMap::JoyController1Port };
  wml::controllers::Joystick joy2{ ControlMap::JoyController2Port };

  #else

  wml::controllers::XboxController xbox1{ ControlMap::XboxController1Port };
  wml::controllers::XboxController xbox2{ ControlMap::XboxController2Port };

  #endif

  // Drive System
  struct DriveSystem {
    wml::TalonSrx Lsrx{ ControlMap::DriveSRXportL };
    wml::TalonSrx Rsrx{ ControlMap::DriveSRXportR };
    wml::VictorSpx Lspx{ ControlMap::DriveSPXportL };
    wml::VictorSpx Rspx{ ControlMap::DriveSPXportR };

    // @TODO: Add encoders to drivetrain gearboxes

    wml::Gearbox LGearBox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Lsrx, Lspx)), nullptr };
    wml::Gearbox RGearbox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Rsrx, Rspx)), nullptr };

    wml::DrivetrainConfig driveTrainConfig{ LGearbox, RGearBox };
    wml::Drivetrain drivetrain{ driveTrainConfig };
    wml::control::PIDGains gainsVelocity{ "Drivetrain Velocity", 1 };
  };
  DriveSystem driveSystem;

};