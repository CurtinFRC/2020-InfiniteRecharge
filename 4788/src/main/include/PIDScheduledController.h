#pragma once

// From wml/control/PIDController

#include "NTUtil/Slave.h"
#include "control/Filter.h"
#include "control/PIDController.h"

#include <string>
#include <memory>

using PIDGains = wml::control::PIDGains;

class PIDScheduledController {
 public:
  PIDScheduledController(PIDGains defaultGains, double setpoint = 0);

  void SetGains(PIDGains gains);
  PIDGains &GetGains();

  void SetSetpoint(double setpoint, bool reset = true);
  double GetSetpoint();

  void SetIZone(double threshIZone);
  void SetWrap(double range);
  bool IsDone();
  void SetIsDoneThreshold(double threshAvgPos, double threshAvgVel);

  double Calculate(double processVariable, double dt, double feedforward = 0.0);

 protected:
  void Reset();

 private:
  PIDGains _gains;
  wml::control::LinearFilter _filterPos, _filterVel;

  double Wrap(double val);

  double _setpoint;

  double _integral;
  double _derivative;
  double _lastError;
  double _avgError, _avgVel;
  int _iterations = 0;    // Used to check if we have sufficient size in avgError.

  double _threshIZone = -1;
  double _threshAvgPos = -1, _threshAvgVel = -1;
  double _wrapRange = -1;
  bool _threshAvgSet = false; // Used to check if _threshAvg has already been manually set.
};