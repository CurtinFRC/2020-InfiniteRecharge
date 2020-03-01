#include "ControlMap.h"

using hand = frc::XboxController::JoystickHand; // Only for FRC controllers

// using namespace wml
using namespace wml;
using namespace wml::controllers;

void ControlMap::InitSmartControllerGroup(SmartControllerGroup &contGroup) {
  contGroup.GetController(ControlMap::TurretAutoAimAxis.cont).Map(ControlMap::TurretAutoAimAxis, ControlMap::TurretAutoAim, ControlMap::triggerDeadzone);

  contGroup.GetController(ControlMap::ShiftMagazinePOV.cont).Map(ControlMap::ShiftMagazinePOV, {
    { Controller::POVPos::kTop, ControlMap::ShiftUpMagazine },
    { Controller::POVPos::kBottom, ControlMap::ShiftDownMagazine }
  });
}


// -------------Defined Ports/Values-------------------

// Controllers
#if __CONTROLMAP_USING_JOYSTICK__
  const int ControlMap::JoyController1Port = 0;
  const int ControlMap::JoyController2Port = 1;
#else
  const int ControlMap::XboxController1Port = 0;
  const int ControlMap::XboxController2Port = 1;
  const int ControlMap::JoyController3Port = 2;
#endif

// Deadzones
const double ControlMap::joyDeadzone = 0.15;
const double ControlMap::xboxDeadzone = 0.1;
const double ControlMap::triggerDeadzone = 0.15;

// PCMs
const int ControlMap::PCModule = 1;

// Drive Left
const int ControlMap::DriveMAXportFL = 12; // 10
const int ControlMap::DriveMAXportBL = 13; // 11
// Drive Right
const int ControlMap::DriveMAXportFR = 10; // 12
const int ControlMap::DriveMAXportBR = 11; // 13
// Drive Gearing
const int ControlMap::ChangeGearPort1 = 0; // 0
const int ControlMap::ChangeGearPort2 = 1; // 1
const int ControlMap::Shift2PTOPort1 = 4; // 4
const int ControlMap::Shift2PTOPort2 = 5; // 5
const double ControlMap::ChangeGearTime = 0;
// Ratchet
const int ControlMap::PTORatchetLeftPort = 99;
const int ControlMap::PTORatchetRightPort = 99;
const double ControlMap::PTORatchetLeftPosition = 0.5;
const double ControlMap::PTORatchetRightPosition = 0.5;
// Drive General Values
const double ControlMap::MaxDrivetrainAcceleration = 0.015; // 0.015
const double ControlMap::MaxDrivetrainSpeed = 1;
const double ControlMap::DriveTestCaseRotations = 50;

// Turret
const int ControlMap::TurretFlyWheelPort = 22; // 20
const int ControlMap::TurretFlyWheelPort2 = 21; // 21
const int ControlMap::TurretAnglePort = 20; // 22
const int ControlMap::TurretRotationPort = 23; // 23
const bool ControlMap::TuneTurretPID = true;
const bool ControlMap::TuneAnglePID = false;

const int ControlMap::TurretLeftLimitPort = 99;
const int ControlMap::TurretRightLimitPort = 99;
const int ControlMap::TurretAngleDownLimitPort = 99;
const bool ControlMap::TurretLeftLimitInvert = false;
const bool ControlMap::TurretRightLimitInvert = false;
const bool ControlMap::TurretAngleDownLimitInvert = false;

const double ControlMap::TurretZeroTimeoutSeconds = 5;
const double ControlMap::TurretEncoderSafeZone = 5;
const double ControlMap::TurretEncoderRotations = 500;
const double ControlMap::MaxAngleEncoderRotations = 500;
const double ControlMap::TurretRatio = 24; // 24:1
const double ControlMap::TurretGearBoxRatio = 40; // 40:1

const double ControlMap::MaxTurretSpeed = 0.3;
const double ControlMap::MaxTurretAngularSpeed = 0.3;
const double ControlMap::FlyWheelVelocity = 50;

const int ControlMap::FlyWheelEncoderPort1 = 1;
const int ControlMap::FlyWheelEncoderPort2 = 2;
const int ControlMap::AngleEncoderPort1 = 3;
const int ControlMap::AngleEncoderPort2 = 4;

// Angle Setpoints (Encoder Values)
const double ControlMap::AngleSetpoint1 = 0;
const double ControlMap::AngleSetpoint2 = 0.1;
const double ControlMap::AngleSetpoint3 = 0.2;
const double ControlMap::AngleSetpoint4 = 0.3;
const double ControlMap::AngleSetpoint5 = 0.4;
const double ControlMap::AngleSetpoint6 = 0.5;
const double ControlMap::AngleSetpoint7 = 0.6;
const double ControlMap::AngleSetpoint8 = 0.7;
const double ControlMap::AngleSetpoint9 = 0.8;
const double ControlMap::AngleSetpoint10 = 0.9;

// Intake
const int ControlMap::IntakeMotorPort = 24; // 24
const int ControlMap::IntakeDownPort1 = 6; // 6
const int ControlMap::IntakeDownPort2 = 7; // 7
const double ControlMap::PannelActuationTime = 0;
const double ControlMap::IntakeDownActuationTime = 0;
const double ControlMap::IntakeTestCaseRotations = 30;


// MagLoader
const int ControlMap::MagLoaderMotorPort = 25; // 25
const int ControlMap::StartMagLimitPort = 1;
const int ControlMap::Position1LimitPort = 3;
const int ControlMap::Position5LimitPort = 2;
const double ControlMap::MagazineBallThreshStart = 650;
const double ControlMap::MagazineBallThreshFinal = 1000; // 1300
const double ControlMap::MagazineBallThreshIndex = 2000;
const double ControlMap::MagTestCaseRotations = 5;

// Climber 
const int ControlMap::ClimberActuatorPort1 = 2; // 2
const int ControlMap::ClimberActuatorPort2 = 3; // 3
const double ControlMap::ClimberActuationTime = 2;

const int ControlMap::ClimberMotor1Port = 27; // 27
const int ControlMap::ClimberMotor2Port = 26; // 26
const double ControlMap::ShiftPTOActuationTime = 0.2;
const double ControlMap::LiftMaxSpeed = 0.5;

// Control System
const int ControlMap::PressureSensorPort = 99;
const int ControlMap::CompressorPort = 0;
const int ControlMap::CamFOV = 60;


//Control Pannel
const int ControlMap::ControlPannelPort = 28; // 28
const int ControlMap::ControlPannelUpPort = 29; // 29

// Auto Values (In Meters)
const double ControlMap::AutoGearRatio = 7; // AutoGearRatio:1/output roation (15 = Neo Drive)
const double ControlMap::WheelDiameter = 15.24; // CM

// Auto Speed
const double ControlMap::MaxAutoDrivetrainSpeed = 0.4;
const double ControlMap::MaxAutoTurnSpeed = 0.25;


// LeftDrive
const double ControlMap::DriveKp = 0.02;
const double ControlMap::DriveKi = 0.01;
const double ControlMap::DriveKd = 0;


// -------------Defined Buttons-------------------

// Turret PID Tuner
const tButton ControlMap::kpUP{ DevController, XboxController::kB };
const tButton ControlMap::kpDOWN{ DevController, XboxController::kA };
const tButton ControlMap::kiUP{ DevController, XboxController::kY };
const tButton ControlMap::kiDOWN{ DevController, XboxController::kX };
const tButton ControlMap::kdUP{ DevController, XboxController::kStart };
const tButton ControlMap::kdDOWN{ DevController, XboxController::kBack };

// Drive System
#if __CONTROLMAP_USING_JOYSTICK__
  const tAxis ControlMap::DrivetrainForward{ Driver, Joystick::kYAxis };
  const tAxis ControlMap::DrivetrainTurn{ Driver, Joystick::kZAxis };
  const tButton ControlMap::ReverseDrivetrain{ Driver, 2 };
  const tButton ControlMap::ShiftGears{ Driver, 99 };
#else
  const tAxis ControlMap::DrivetrainLeft{ Driver, XboxController::kLeftYAxis };
  const tAxis ControlMap::DrivetrainRight{ Driver, XboxController::kRightYAxis };
  const tButton ControlMap::ReverseDrivetrain{ Driver, XboxController::kStart };
  const tButton ControlMap::ShiftGears{ Driver, XboxController::kBumperRight };
#endif

// Turret
#if __CONTROLMAP_USING_JOYSTICK__
  //@todo
#else
  const tAxis ControlMap::TurretAutoAimAxis{ CoDriver, XboxController::kLeftThrottle };
  const std::vector<tButton> ControlMap::TurretAutoAim{ {CoDriver, 30}, {DevController, 30} };

  const tAxis ControlMap::TurretManualRotate{ CoDriver, XboxController::kRightXAxis };
  const tAxis ControlMap::TurretManualAngle{ CoDriver, XboxController::kLeftYAxis };
  const tAxis ControlMap::TurretFlyWheelSpinUp{ CoDriver, XboxController::kRightThrottle };

  const tButton ControlMap::TurretFire{ CoDriver, XboxController::kA };
  const tButton ControlMap::RevFlyWheel{CoDriver, XboxController::kBack};

  const tButton ControlMap::Ball3Fire{ CoDriver, XboxController::kBumperRight}; // just for auto testing 
#endif


// Intake 
#if __CONTROLMAP_USING_JOYSTICK__
  const tButton ControlMap::Intake{ Driver, 11 };
  const tButton ControlMap::Intake{ Driver, 12 };
#else 
  const tAxis ControlMap::Intake{ CoDriver, XboxController::kRightThrottle };
  const tAxis ControlMap::Outake{ CoDriver, XboxController::kLeftThrottle };
  const std::vector<tButton> ControlMap::DownIntake{ { CoDriver, XboxController::kX }, { Driver, XboxController::kY } }; // Allows both driver and co driver to access the button
#endif

//Control Pannel
#if __CONTROLMAP_USING_JOYSTICK__
  //please change if we ever use a joystick 
  const tPOV ControlMap::ControlPannelUp{ Driver, 8};
  const tPOV ControlMap::SpinControlPannelLeft{ Driver, 7};
  const tPOV ControlMap::ControlPannelDown{ Driver, 6};
  const tPOV ControlMap::SpinControlPannelRight{ Driver, 5};
#else 
  const tPOV ControlMap::ControlPannelUp{ Driver, XboxController::kTop};
  const tPOV ControlMap::SpinControlPannelLeft{ Driver, XboxController::kLeft};
  const tPOV ControlMap::ControlPannelDown{ Driver, XboxController::kBottom};
  const tPOV ControlMap::SpinControlPannelRight{ Driver, XboxController::kRight};
#endif

// MagLoader
const tPOV ControlMap::ShiftMagazinePOV{ CoDriver, 0 };
#if __CONTROLMAP_USING_JOYSTICK__

#else
  const tButton ControlMap::ShiftUpMagazine{ CoDriver, __LINE__ + 30 };
  const tButton ControlMap::ShiftDownMagazine{ CoDriver, __LINE__ + 30 };

  const tButton ControlMap::ManualMag{ CoDriver, XboxController::kB };
#endif

//Climber 
#if __CONTROLMAP_USING_JOYSTICK__
//please change
  const tAxis ControlMap::ClimberControl{ CoDriver, 2 };
#else
  const tAxis ControlMap::ClimberControlLeft{ CoDriver, XboxController::kLeftYAxis};
  const tAxis ControlMap::ClimberControlRight{ CoDriver, XboxController::kRightYAxis};
  const tButton ControlMap::ClimberToggle{ CoDriver, XboxController::kY};
  const tButton ControlMap::Shift2PTO{ Driver, XboxController::kBumperLeft };
#endif