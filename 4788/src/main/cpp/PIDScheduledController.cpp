#include "PIDScheduledController.h"

#include <cmath>
#include <frc/smartdashboard/SendableBase.h>
#include <frc/smartdashboard/SendableBuilder.h>

#include <networktables/NetworkTableInstance.h>

#include <iostream>

PIDScheduledController::PIDScheduledController(PIDGains gains, double setpoint) : _gains(gains), _filterPos(LinearFilter::MovingAverage(20)), _filterVel(LinearFilter::MovingAverage(20)), _setpoint(setpoint), _lastError(0) {}

void PIDScheduledController::SetGains(PIDGains gains) {
  _gains = gains;
}

PIDGains &PIDScheduledController::GetGains() {
  return _gains;
}

void PIDScheduledController::SetSetpoint(double setpoint, bool reset) {
  if (reset) Reset();
  _setpoint = setpoint;
  if (_threshAvgSet == false) {
    _threshAvgPos = setpoint * 0.05;
    _threshAvgVel = setpoint * 0.05;
  }
}

double PIDScheduledController::GetSetpoint() {
  return _setpoint;
}

void PIDScheduledController::SetIZone(double threshIZone) {
  _threshIZone = threshIZone;
}

bool PIDScheduledController::IsDone() {
  return _iterations > 20 && std::abs(_avgError) < _threshAvgPos && std::abs(_avgVel) < _threshAvgVel;
}

void PIDScheduledController::SetIsDoneThreshold(double threshAvgPos, double threshAvgVel) {
  _threshAvgPos = threshAvgPos;
  _threshAvgVel = threshAvgVel;
  _threshAvgSet = true;
}

void PIDScheduledController::SetWrap(double range) {
  _wrapRange = range;
}

double PIDScheduledController::Calculate(double processVariable, double dt, double feedforward) {
  double error = Wrap(_setpoint - processVariable);
  _avgError = _filterPos.Get(error);

  if (_threshIZone > 0 && std::abs(error) > _threshIZone) _integral = 0; // I zone
  else _integral += error * dt; // Calc I
  _derivative = dt > 0 ? (error - _lastError) / dt : 0; // Calc D
  _avgVel = _filterVel.Get(_derivative);

  double output = _gains.GetkP() * error + _gains.GetkI() * _integral + _gains.GetkD() * _derivative + _gains.GetkF() * feedforward;
  _lastError = error;
  _iterations++;

  return output;
}

void PIDScheduledController::Reset() {
  _integral = 0;
  _derivative = 0;
  _lastError = 0;
  _iterations = 0;
  _filterPos.Reset();
  _filterVel.Reset();
  // Does not reset _threshAvg, use SetIZone instead
}

double PIDScheduledController::Wrap(double val) {
  if (_wrapRange > 0) {
    val = std::fmod(val, _wrapRange);
    if (std::abs(val) > (_wrapRange / 2.0)) {
      return (val > 0) ? val - _wrapRange : val + _wrapRange;
    }
  }

  return val;
}