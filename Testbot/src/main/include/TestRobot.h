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
#include "sensors/LimitSwitch.h"


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

  wml::controllers::XboxController *xbox1;

  wml::sensors::LimitSwitch LimitSwitch0{0, false};
  wml::sensors::LimitSwitch LimitSwitch1{1, false};
  wml::sensors::LimitSwitch LimitSwitch2{2, false};
  wml::VictorSpx *BeltMotor;


  wml::Gearbox *left, *right;
  wml::Drivetrain *drivetrain;

  frc::DoubleSolenoid *hatchEjector;

  nt::NetworkTableEntry TargetX;
  nt::NetworkTableEntry TargetY;
  nt::NetworkTableEntry ImageHeight;
  nt::NetworkTableEntry ImageWidth;
  std::shared_ptr<nt::NetworkTable> table;
};
