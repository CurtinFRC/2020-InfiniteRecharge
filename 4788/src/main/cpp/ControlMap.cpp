#include "ControlMap.h"

using hand = frc::XboxController::JoystickHand; // Only for FRC controllers

// using namespace wml
using namespace wml;
using namespace wml::controllers;

void ControlMap::InitSmartControllerGroup(SmartControllerGroup &contGroup) {}


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
const double ControlMap::joyDeadzone = 0.05;
const double ControlMap::xboxDeadzone = 0.05;
const double ControlMap::triggerDeadzone = 0.05;

// Drive Left
const int ControlMap::DriveMAXportFL = 99;
const int ControlMap::DriveMAXportBL = 99;
// Drive Right
const int ControlMap::DriveMAXportFR = 99;
const int ControlMap::DriveMAXportBR = 99;
// Drive Gearning
const int ControlMap::ChangeGearPort1 = 99;
const int ControlMap::ChangeGearPort2 = 99;
const double ControlMap::ChangeGearTime = 0;

// Turret
const int ControlMap::TurretFlyWheelPort = 7;
const int ControlMap::TurretAnglePort = 99;
const int ControlMap::TurretRotationPort = 5;

const double ControlMap::TurretDistanceSetpoint1 = 0; // Close
const double ControlMap::TurretDistanceSetpoint2 = 0; // Mid
const double ControlMap::TurretDistanceSetpoint3 = 0; // Far

const int ControlMap::TurretLeftLimitPort = 99;
const int ControlMap::TurretRightLimitPort = 99;
const int ControlMap::TurretAngleDownLimitPort = 99;

const bool ControlMap::TurretLeftLimitInvert = false;
const bool ControlMap::TurretRightLimitInvert = false;
const bool ControlMap::TurretAngleDownLimitInvert = false;

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

// Climber 
const int ControlMap::ClimberActuatorPort1 = 99;
const int ControlMap::ClimberActuatorPort2 = 99;
const double ControlMap::ClimberActuationTime = 0.2;

const int ControlMap::ClimberMotor1Port = 99;
const int ControlMap::ClimberMotor2Port = 99;

const int ControlMap::Shift2PTOPort = 99;
const int ControlMap::Shift2PTOForwardPosition = 20;
const int ControlMap::Shift2PTOReversePosition = 99;

// Control System
const int ControlMap::PressureSensorPort = 99;
const int ControlMap::CompressorPort = 99;

//Control Pannel
const int ControlMap::ControlPannelPort = 99;
const int ControlMap::ControlPannelUpPort = 99;


// -------------Defined Buttons-------------------

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
  const tButton ControlMap::ShiftGears{ Driver, XboxController::kBumperLeft };
#endif

// Turret
#if __CONTROLMAP_USING_JOYSTICK__
  //@todo
#else
  const tAxis ControlMap::TurretAutoAim{ CoDriver, XboxController::kLeftThrottle };
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

//Wheel of cringe 
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
#if __CONTROLMAP_USING_JOYSTICK__

#else
  const tPOV ControlMap::ShiftUpMagazine{ CoDriver, XboxController::kTop };
  const tPOV ControlMap::ShiftDownMagazine{ CoDriver, XboxController::kBottom };
#endif

//Climber 
#if __CONTROLMAP_USING_JOYSTICK__
//please change
  const tAxis ControlMap::ClimberControl{ CoDriver, 2};
#else
  const tAxis ControlMap::ClimberControl{ CoDriver, XboxController::kLeftYAxis};
#endif