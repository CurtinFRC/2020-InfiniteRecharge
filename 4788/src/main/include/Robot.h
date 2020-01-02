#pragma once

#include <iostream>

#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/DoubleSolenoid.h>
#include <frc/GenericHID.h>

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableInstance.h>

#include "strategy/StrategyController.h"
#include "strategy/MPStrategy.h"
#include "NTProvider.h"
#include "WMLCtre.h"
#include "controllers/Controllers.h"
#include "Gearbox.h"
#include "actuators/BinaryServo.h"
#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"
#include "actuators/VoltageController.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"
#include "sensors/PressureSensor.h"

#include <cameraserver/CameraServer.h>
#include <frc/DriverStation.h> 

#include "Toggle.h"


class Robot : public frc::TimedRobot, protected wml::StrategyController, protected wml::NTProvider {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void DisabledInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  // controllers
  frc::XboxController *xbox;

  // Drivebase
  frc::Spark *leftMotor[1];
  frc::Spark *rightMotor[1];

  // Hammer
  frc::Spark *hammer[1];

  // Pneumatics. For a reason i don't know yet

  // Construct a compressor instance plugged into the default PCM
  wml::actuators::Compressor compressor{};

  // Construct a (double-actuating) solenoid instance plugged into ports 0 and 1 on the default PCM, which takes roughly 0.2 secs to actuate.
  wml::actuators::DoubleSolenoid solenoid{ 0, 1, 0.2 };

  // Construct an analogue pressureSensor instance plugged into analogue port 0
  wml::sensors::PressureSensor pressureSensor{ 0 };

};
