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
#include "NTProvider.h"
#include "CurtinCtre.h"
#include "controllers/CurtinControllers.h"
#include "Gearbox.h"
#include "actuators/BinaryServo.h"
#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"
#include "actuators/VoltageController.h"
#include "sensors/Encoder.h"
#include "sensors/LimitSwitch.h"
#include "sensors/NavX.h"
#include "sensors/PressureSensor.h"

#include "Toggle.h"

// Local Files
#include "ControlMap.h"
#include "Drivetrain.h"
#include "DriveSystem.h"
#include "SubSystem1.h"
#include "SubSystem2.h"
#include "PenumaticSystem1.h"
#include "PenumaticSystem2.h"

class Robot : public frc::TimedRobot, protected curtinfrc::StrategyController, protected curtinfrc::NTProvider {
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

  // Definements

  bool enableFOC = false; // not needed for driving unless REALLY REALLY required
  curtinfrc::Toggle fallToggle; // this isn't needed unless elevator robot

  // Instances
  ControlMap *controlMap;
  DriveSystem *driveSystem;
  SubSystem1 *subSystem1;
  SubSystem2 *subSystem2;
  PneumaticSystem1 *pneumaticSystem1;
  PneumaticSystem2 *pneumaticSystem2;

  // ----------Pneumatics--------------
  // Compressor
  curtinfrc::actuators::Compressor *compressor;
};
