#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"

struct RobotMap {
  #if __CONTROLMAP__USING_JOYSTICK__

  curtinfrc::controllers::Joystick joy1{ ControlMap::JoyController1Port };
  curtinfrc::controllers::Joystick joy2{ ControlMap::JoyController2Port };

  #else

  curtinfrc::controllers::XboxController xbox1{ ControlMap::XboxController1Port };
  curtinfrc::controllers::XboxController xbox2{ ControlMap::XboxController2Port };

  #endif

  // Drive System
  curtinfrc::TalonSrx DriveMotorLsrx{ ControlMap::DriveSRXportL };
  curtinfrc::TalonSrx DriveMotorRsrx{ ControlMap::DriveSRXportR };
  curtinfrc::VictorSpx DriveMotorLspx{ ControlMap::DriveSPXportL};
  curtinfrc::VictorSpx DriveMotorRspx{ ControlMap::DriveSPXportR};

  // Subsystem1
  curtinfrc::TalonSrx SubSystem1SRX1{ ControlMap::Sub1SRXport1 };
  curtinfrc::TalonSrx SubSystem1SRX2{ ControlMap::Sub1SRXport2 };

  // Subsystem2
  curtinfrc::VictorSpx SubSystem2SPX{ ControlMap::Sub2SPXport1 };
};