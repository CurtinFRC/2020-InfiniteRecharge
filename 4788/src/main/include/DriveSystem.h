#pragma once

#include <string>

#include "devices/StateDevice.h"
#include "Gearbox.h"
#include "control/PIDController.h"
#include "strategy/StrategySystem.h"
#include "control/MotorFilters.h"

#include "Usage.h"

struct DriveSystemConfig {
  wml::Gearbox &gearbox;
  wml::Drivetrain &drivetrain;

  std::string name = "<DriveSystem>";
};

enum class DriveSystemState { kStationary = 0, kMoving, kManual };

class DriveSystem : public wml::devices::StateDevice<DriveSystemState>, public wml::StrategySystem {
  public:
  DriveSystem(DriveSystemConfig config, wml::control::PIDGains gain) : StateDevice(config.name), _config(config), _gain(gain), _controller(gain), _current_filter(-80.0, 120.0, config.gearbox) {};

  virtual std::string GetStateString() final;

  void SetManual(double power);
  void SetHold();

  double GetCurrentPosition();

  DriveSystemConfig &GetConfig();
  
  protected:
  virtual void OnStatePeriodic(DriveSystemState state, double dt) override;

  private:
  DriveSystemConfig _config;

  wml::control::PIDGains _gain;
  wml::control::PIDController _controller;
  wml::control::CurrentFFFilter _current_filter;

  wml::Usage<DriveSystemConfig>::Scoped _usage{&_config};
};
