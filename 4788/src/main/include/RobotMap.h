#pragma once

// #include "GeneralLibs/GeneralLibs.h"

#include "SubSystem1.h"
#include "SubSystem2.h"

struct RobotMap {
  #if __CONTROLMAP__USING_JOYSTICK__

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

    wml::Gearbox LGearbox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Lsrx, Lspx)), nullptr };
    wml::Gearbox RGearbox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(Rsrx, Rspx)), nullptr };

    wml::DrivetrainConfig driveTrainConfig{ LGearbox, RGearbox };
    wml::Drivetrain drivetrain{ driveTrainConfig };
    wml::control::PIDGains gainsVelocity{ "Drivetrain Velocity", 1 };
  };

  DriveSystem driveSystem;

  // Subsystem1
  struct Subsystem1 {
    wml::TalonSrx SRX1{ ControlMap::Sub1SRXport1 };
    wml::TalonSrx SRX2{ ControlMap::Sub1SRXport2 };
    
    wml::sensors::DigitalEncoder encoder{ 4, 5, 1024 };
    wml::Gearbox gearbox{ new wml::actuators::MotorVoltageController(wml::actuators::MotorVoltageController::Group(SRX1, SRX2)), &encoder };
    SubSystem1Config subSystem1Config{ gearbox };
  };

  // Subsystem2
  struct Subsystem2 {
    wml::VictorSpx SPX{ ControlMap::Sub2SPXport1 };
  };

};