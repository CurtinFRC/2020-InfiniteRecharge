#include "SubSystem1.h"

#include <iostream>
#include <cmath>

// public

std::string SubSystem1::GetStateString() {
  switch (GetState()) {
   case SubSystem1State::kStationary:
    return "kStationary";
    
   case SubSystem1State::kMoving:
    return "kMoving";
    
   case SubSystem1State::kManual:
    return "kManual";
  }

  return "<state error>";
}


void SubSystem1::SetManual(double power) {
  SetState(SubSystem1State::kManual);
  _controller.SetSetpoint(power);
}

void SubSystem1::SetSetpoint(double setpoint) {
  SetState(SubSystem1State::kMoving);
  _controller.SetSetpoint(setpoint);
}

void SubSystem1::SetHold() {
  SetState(SubSystem1State::kStationary);
  _controller.SetSetpoint(GetCurrentPosition() + 0.1);
}


double SubSystem1::GetSetpoint() {
  return _controller.GetSetpoint();
}

double SubSystem1::GetCurrentPosition() {
  return _config.gearbox.encoder->GetEncoderRotations();
}

SubSystem1Config &SubSystem1::GetConfig() {
  return _config;
}

// virtual

void SubSystem1::OnStatePeriodic(SubSystem1State state, double dt) {
  double voltage = 0;
  
  switch (state) {
   case SubSystem1State::kManual:
    voltage = _controller.GetSetpoint();
    break;

   case SubSystem1State::kMoving:
    if (_controller.IsDone()) SetHold(); // Good enough EPS for now
   case SubSystem1State::kStationary:
    voltage = _controller.Calculate(GetCurrentPosition(), dt);
    break;
  }

  // Limiters
  // if (_config.limitSensorTop != nullptr)
  //   if (voltage > 0)
  //     if (_config.limitSensorTop->Get())
  //       voltage = 0;

  // if (_config.limitSensorBottom != nullptr)
  //   if (voltage < 0)
  //     if (_config.limitSensorBottom->Get()) {
  //       voltage = 0;
  //       GetConfig().spool.encoder->ZeroEncoder();
  //     }

  voltage = std::min(12.0, std::max(-12.0, voltage)) * 0.7;
  voltage = _current_filter.Get(voltage);
  GetConfig().gearbox.transmission->SetVoltage(voltage);
}
