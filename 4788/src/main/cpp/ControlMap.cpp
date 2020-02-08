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
#endif

// Deadzones
const double ControlMap::joyDeadzone = 0.15;
const double ControlMap::xboxDeadzone = 0.1;
const double ControlMap::triggerDeadzone = 0.15;

// Drive Left
const int ControlMap::DriveMAXportFL = 4;
const int ControlMap::DriveMAXportBL = 3;
// Drive Right
const int ControlMap::DriveMAXportFR = 1;
const int ControlMap::DriveMAXportBR = 2;
// Drive Gearing
const int ControlMap::ChangeGearPort1 = 99;
const int ControlMap::ChangeGearPort2 = 99;
const int ControlMap::Shift2PTOPort1 = 99;
const int ControlMap::Shift2PTOPort2 = 99;
const double ControlMap::ChangeGearTime = 0;
// Drive General Values
const double ControlMap::MaxDrivetrainAcceleration = 0.015;
const double ControlMap::MaxDrivetrainSpeed = 1;
const double ControlMap::DriveTestCaseRotations = 50;

// Turret
const int ControlMap::TurretFlyWheelPort = 5;
const int ControlMap::TurretFlyWheelPort2 = 6;
const int ControlMap::TurretAnglePort = 99;
const int ControlMap::TurretRotationPort = 8;
const bool ControlMap::TuneTurretPID = false;
const bool ControlMap::TuneAnglePID = true;

const double ControlMap::TurretDistanceSetpoint1 = 0; // Close
const double ControlMap::TurretDistanceSetpoint2 = 0; // Mid
const double ControlMap::TurretDistanceSetpoint3 = 0; // Far

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
const double ControlMap::TurretRatio = 7;
const double ControlMap::MaxTurretSpeed = 0.5;
const double ControlMap::MaxTurretAngularSpeed = 0.5;
const double ControlMap::FlyWheelVelocity = 500;

// Angle Setpoints (Encoder Values)
const double ControlMap::AngleSetpoint1 = 100;
const double ControlMap::AngleSetpoint2 = 110;
const double ControlMap::AngleSetpoint3 = 120;
const double ControlMap::AngleSetpoint4 = 130;
const double ControlMap::AngleSetpoint5 = 140;
const double ControlMap::AngleSetpoint6 = 150;
const double ControlMap::AngleSetpoint7 = 160;
const double ControlMap::AngleSetpoint8 = 170;
const double ControlMap::AngleSetpoint9 = 180;
const double ControlMap::AngleSetpoint10 = 190;

// Intake
const int ControlMap::IntakeMotorPort = 99;
const int ControlMap::IntakeDownPort1 = 99;
const int ControlMap::IntakeDownPort2 = 99;
const double ControlMap::PannelActuationTime = 0;
const double ControlMap::IntakeDownActuationTime = 99;


// MagLoader
const int ControlMap::MagLoaderMotorPort = 99;
const int ControlMap::StartMagLimitPort = 99;
const int ControlMap::Position1LimitPort = 99;
const int ControlMap::Position5LimitPort = 99;
const double ControlMap::MagTestCaseRotations = 5;

// Climber 
const int ControlMap::ClimberActuatorPort1 = 99;
const int ControlMap::ClimberActuatorPort2 = 99;
const double ControlMap::ClimberActuationTime = 0.2;

const int ControlMap::ClimberMotor1Port = 99;
const int ControlMap::Shift1PTOPort = 99;
const int ControlMap::Shift2PTOPort = 99;
const double ControlMap::ShiftPTOActuationTime = 0.2;
const double ControlMap::LiftMaxSpeed = 0.5;

// Control System
const int ControlMap::PressureSensorPort = 99;
const int ControlMap::CompressorPort = 99;
const int ControlMap::CamFOV = 60;

//Control Pannel
const int ControlMap::ControlPannelPort = 99;
const int ControlMap::ControlPannelUpPort = 99;
const int ControlMap::ControlPannelUpSolPort1 = 99;
const int ControlMap::ControlPannelUpSolPort2 = 99;
const double ControlMap::ControlPannelActuationTime = 99;


// -------------Defined Buttons-------------------

// Turret PID Tuner
const tButton ControlMap::kpUP{ CoDriver, XboxController::kB };
const tButton ControlMap::kpDOWN{ CoDriver, XboxController::kA };
const tButton ControlMap::kiUP{ CoDriver, XboxController::kY };
const tButton ControlMap::kiDOWN{ CoDriver, XboxController::kX };
const tButton ControlMap::kdUP{ CoDriver, XboxController::kStart };
const tButton ControlMap::kdDOWN{ CoDriver, XboxController::kBack };

// Drive System
#if __CONTROLMAP_USING_JOYSTICK__
  const tAxis ControlMap::DrivetrainForward{ Driver, Joystick::kYAxis };
  const tAxis ControlMap::DrivetrainTurn{ Driver, Joystick::kZAxis };
  const tButton ControlMap::ReverseDrivetrain{ Driver, 2 };
  const tButton ControlMap::ShiftGears{ Driver, 99 };
  const tButton ControlMap::Shift2PTO{ CoDriver, 99 };
#else
  const tAxis ControlMap::DrivetrainLeft{ Driver, XboxController::kLeftYAxis };
  const tAxis ControlMap::DrivetrainRight{ Driver, XboxController::kRightYAxis };
  const tButton ControlMap::ReverseDrivetrain{ Driver, XboxController::kStart };
  const tButton ControlMap::ShiftGears{ Driver, XboxController::kBumperLeft };
#endif

// Turret
#if __CONTROLMAP_USING_JOYSTICK__
  //@todo
#else
  const tAxis ControlMap::TurretAutoAimAxis{ CoDriver, XboxController::kLeftThrottle };
  const tButton ControlMap::TurretAutoAim{ CoDriver, 30 };

  const tAxis ControlMap::TurretManualRotate{ CoDriver, XboxController::kRightXAxis };
  const tAxis ControlMap::TurretManualAngle{ CoDriver, XboxController::kRightYAxis };
  const tAxis ControlMap::TurretFlyWheelSpinUp{ CoDriver, XboxController::kRightThrottle };
  
  const tButton ControlMap::TurretFire{ CoDriver, XboxController::kA };
#endif

// Intake 
#if __CONTROLMAP_USING_JOYSTICK__
  const tButton ControlMap::Intake{ Driver, 11 };
  const tButton ControlMap::Intake{ Driver, 12 };
#else 
  const tAxis ControlMap::Intake{ Driver, XboxController::kRightThrottle};
  const tAxis ControlMap::Outake{ Driver, XboxController::kLeftThrottle};
  const tButton ControlMap::DownIntake{ Driver, XboxController::kY};
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
  const tButton ControlMap::ManualMag{ CoDriver, XboxController::kBack};
#endif

//Climber 
#if __CONTROLMAP_USING_JOYSTICK__
//please change
  const tAxis ControlMap::ClimberControl{ CoDriver, 2};
#else
  const tAxis ControlMap::ClimberControl{ CoDriver, XboxController::kLeftYAxis};
  const tButton ControlMap::ClimberUp{ CoDriver, XboxController::kX };
  const tButton ControlMap::Shift2PTO{ CoDriver, XboxController::kBumperRight };
#endif