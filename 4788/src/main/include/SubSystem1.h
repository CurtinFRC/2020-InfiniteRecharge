#pragma once

#include <string>

#include "devices/StateDevice.h"
#include "control/PIDController.h"
#include "strategy/StrategySystem.h"
#include "control/MotorFilters.h"
#include "Gearbox.h"
#include "strategy/Strategy.h"
#include "controllers/Controllers.h"
#include "sensors/BinarySensor.h"

#include "Usage.h"

struct SubSystem1Config {
  wml::Gearbox &gearbox;

  wml::sensors::BinarySensor *upperLimitSensor, *lowerLimitSensor;

  std::string name = "<SubSystem1>";
};

enum class SubSystem1State { kStationary = 0, kMoving, kManual };

class SubSystem1 : public wml::devices::StateDevice<SubSystem1State>, public wml::StrategySystem {
  public:
  SubSystem1(SubSystem1Config config, wml::control::PIDGains gain) : StateDevice(config.name), _config(config), _gain(gain), _controller(gain), _current_filter(-80.0, 120.0, config.gearbox) {};

  virtual std::string GetStateString() final;

  void SetManual(double power);
  void SetSetpoint(double setpoint);
  void SetHold();

  double GetSetpoint(); // Do we need that?
  double GetCurrentPosition();

  SubSystem1Config &GetConfig();
  
  protected:
  virtual void OnStatePeriodic(SubSystem1State state, double dt) override;

  private:
  SubSystem1Config _config;

  wml::control::PIDGains _gain;
  wml::control::PIDController _controller;
  wml::control::CurrentFFFilter _current_filter;

  wml::Usage<SubSystem1Config>::Scoped _usage{&_config};
};

class SubSystem1ManualStrategy : public wml::Strategy {
 public:
  SubSystem1ManualStrategy(std::string name, SubSystem1 &subsys1, wml::controllers::SmartController &cont1, wml::controllers::SmartController &cont2);

  void OnUpdate(double dt) override;

 private:
  SubSystem1 &_subsys1;
  wml::controllers::SmartController &_cont1, &_cont2;
};

