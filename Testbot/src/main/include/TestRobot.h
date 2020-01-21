#pragma once

#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Spark.h>
#include <frc/Talon.h>
#include <frc/DoubleSolenoid.h>
#include "controllers/Controllers.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

#include "actuators/Compressor.h"
#include "actuators/DoubleSolenoid.h"

#include "sensors/PressureSensor.h"


#include "WMLCtre.h"
#include "Gearbox.h"
#include "Drivetrain.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  double PIDCalc(double dt, double input);

  frc::XboxController *xbox1;
  frc::XboxController *xbox2;
  
  wml::TalonSrx *leftMotor1, *leftMotor2, *rightMotor1, *rightMotor2;
  wml::TalonSrx *TurretRoation;
  wml::TalonSrx *TurretAngle;
  wml::TalonSrx *FlyWheel;

  wml::actuators::Compressor compressor{};
  wml::actuators::DoubleSolenoid solenoid{ 0, 1, 0.2 };
  wml::sensors::PressureSensor pressureSensor{ 0 };


  wml::Gearbox *left, *right;
  wml::Drivetrain *drivetrain;

  frc::DoubleSolenoid *hatchEjector;

  nt::NetworkTableEntry TargetX;
  nt::NetworkTableEntry TargetY;
  nt::NetworkTableEntry ImageHeight;
  nt::NetworkTableEntry ImageWidth;
  std::shared_ptr<nt::NetworkTable> table;
};
