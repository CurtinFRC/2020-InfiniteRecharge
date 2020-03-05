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

// Local Files
#include "ControlMap.h"
#include "RobotMap.h"
#include "DriveSystem.h"
#include "Turret2.h"
#include "Climber2.h"
#include "Intake2.h"
#include "MagLoader2.h"



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

  private:
    // Instances
    RobotMap robotMap;
    wml::Drivetrain *drivetrain;
    Turret *turret;
    MagLoader *magLoader;
    Intake *intake;
    Climber *climber;
    WayFinder *wayFinder;

    // nt
    nt::NetworkTableEntry AutoSelector;
    nt::NetworkTableEntry RobotActive;
};