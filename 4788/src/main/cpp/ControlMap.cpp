#include "ControlMap.h"

using hand = frc::XboxController::JoystickHand; // Only for FRC controllers

// using namespace wml
using namespace wml;
using namespace wml::controllers;

void ControlMap::InitSmartControllerGroup(SmartControllerGroup &contGroup) {}


// -------------Defined Ports-------------------

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
const int ControlMap::DriveSRXportL = 0;
const int ControlMap::DriveSPXportL = 1;
// Drive Right
const int ControlMap::DriveSRXportR = 2;
const int ControlMap::DriveSPXportR = 3;

// Turret
const int ControlMap::TurretFlyWheelPort = 4;
const int ControlMap::TurretAnglePort = 5;
const int ControlMap::TurretRotationPort = 6;

// Intake
const int ControlMap::IntakeMotorPort = 7;

// MagLoader
const int ControlMap::MagLoaderMotorPort = 8;

// Control System
const int ControlMap::PressureSensorPort = 0;
const int ControlMap::CompressorPort = 1;



// -------------Defined Buttons-------------------

// Drive System
#if __CONTROLMAP_USING_JOYSTICK__
  const tAxis ControlMap::DrivetrainForward{ 1, Joystick::kYAxis };
  const tAxis ControlMap::DrivetrainTurn{ 1, Joystick::kZAxis };
  const tButton ControlMap::ReverseDrivetrain{ 1, 2 };
#else
  const tAxis ControlMap::DrivetrainLeft{ Driver, XboxController::kLeftYAxis };
  const tAxis ControlMap::DrivetrainRight{ Driver, XboxController::kRightYAxis };
  const tButton ControlMap::ReverseDrivetrain{ Driver, XboxController::kStart };
#endif

// Turrent
#if __CONTROLMAP_USING_JOYSTICK__
  //@todo
#else
  const tAxis ControlMap::TurretAutoAim{ CoDriver, XboxController::kLeftThrottle };
  const tAxis ControlMap::TurretManualRotate{ CoDriver, XboxController::kRightXAxis };
  const tAxis ControlMap::TurretManualAngle{ CoDriver, XboxController::kLeftYAxis };
  const tAxis ControlMap::TurretFlyWheelSpinUp{ CoDriver, XboxController::kRightThrottle };
  const tButton ControlMap::TurretFire{ CoDriver, XboxController::kA };
#endif

//Intake 
#if __CONTROLMAP_USING_JOYSTICK__
  const tButton ControlMap::Intake{ Driver, 11 };
  const tButton ControlMap::Intake{ Driver, 12 };
#else 
  const tAxis ControlMap::Intake{ Driver, XboxController::kLeftThrottle};
  const tAxis ControlMap::Outake{ Driver, XboxController::kRightThrottle};
#endif