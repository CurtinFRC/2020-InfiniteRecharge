#include "SubSystem1.h"

#include <iostream>
#include <cmath>

#include "ControlMap.h"

using namespace wml;
using namespace wml::controllers;

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

  if (_config.upperLimitSensor != nullptr)
    if (voltage > 0)
      if (_config.upperLimitSensor->Get())
        voltage = 0;

  if (_config.lowerLimitSensor != nullptr)
    if (voltage < 0)
      if (_config.lowerLimitSensor->Get())
        voltage = 0;

  voltage = std::min(12.0, std::max(-12.0, voltage)) * 0.7;
  voltage = _current_filter.Get(voltage);
  _config.gearbox.transmission->SetVoltage(voltage);
}

SubSystem1ManualStrategy::SubSystem1ManualStrategy(std::string name, SubSystem1 &subsys1, SmartController &cont1, SmartController &cont2) : Strategy(name), _subsys1(subsys1), _cont1(cont1), _cont2(cont2) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
} 

void SubSystem1ManualStrategy::OnUpdate(double dt) {
  if (_cont1.Get(ControlMap::SubSystem1Up)) {
    _subsys1.SetManual(ControlMap::SubSystem1Speed);
  } else if (_cont1.Get(ControlMap::SubSystem1Down)) {
    _subsys1.SetManual(-ControlMap::SubSystem1Speed);
  } else {
    _subsys1.SetHold();
  }
}

