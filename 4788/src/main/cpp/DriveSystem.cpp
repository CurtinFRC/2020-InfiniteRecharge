#include "DriveSystem.h"

#include <iostream>
#include <cmath>

using namespace wml;
using namespace frc;
using hand = frc::XboxController::JoystickHand; // can't be bothered writing it out complelty

// public

std::string DriveSystem::GetStateString() {
  switch (GetState()) {
    case DriveSystemState::kStationary:
      return "kStationary";
    
    case DriveSystemState::kManual;
      return "kManual";   
  }

  return "<state error>";
}

void DriveSystem::SetManual(double power) {
  SetState(DriveSystemState::kManual);
  _controller.SetSetpoint(setpoint);
}

void DriveSystem::SetHold() {
  SetState(DriveSystem::kStationary);
  _controller.SetSetpoint(setpoint);
}

double DriveSystem::GetCurrentPosition() {
  return _config;
}

// virtual


void DriveSystem::OnStatePeriodic(DriveSystemState state, double dt) {
  double voltage = 0;

  switch (state) {
    case DriveSystem::kManual:
      voltage = _controller.GetSetpoint();
    break;
    
    case DriveSystem::kMoving:
      if(_controller.IsDone()) SetHold();
    case DriveSystem::kStationary:
      voltage = _controller.Calculate(GetCurrentPosition(), dt);
    break;
  }

  voltage = std::min(12.0, std::max(-12.0, voltage)) * 0.7;
  voltage = _current_filter.Get(voltage);
  GetConfig().gearbox.transmission->SetVoltage(voltage);
}


// -------------Old code use as reference----------------


DriveSystem::DriveSystem(RobotMap *robotMap) {
  // We invert one side of the motors to make it drive straight when both sides are positively/negatively active

  robotMap->Lsrx.SetInverted(true);
  robotMap->Lspx.SetInverted(true);

  robotMap->Rsrx.SetInverted(false);
  robotMap->Rspx.SetInverted(false);


  drivetrain->StartLoop(100);

  DriveSystem::ZeroEncoder();
}

void DriveSystem::ZeroEncoder() {
  // Zero Encoders (Only SRX's Have encoders)
  _robotmap->Lsrx.ZeroEncoder();
  _robotmap->Rsrx.ZeroEncoder();
}

void DriveSystem::DriveControl() {
  
  // Code if we are using joysticks
  #if __CONTROLMAP__USING_JOYSTICK__

  turn_speed = _robotmap->joy1.kYAxis;
  left_speed = _robotmap->joy1.kYAxis + turn_speed;
  right_speed = _robotmap->joy1.kZAxis - turn_speed;
  drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

  #else
  left_speed = _robotmap->xbox1.kLeftYAxis/1.15;
  right_speed = _robotmap->xbox1.kRightYAxis/1.15;
  drivetrain->Set(left_speed*std::abs(left_speed), right_speed*std::abs(right_speed));

  #endif
}