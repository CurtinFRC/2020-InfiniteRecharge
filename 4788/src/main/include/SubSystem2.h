#pragma once

#include <string>

#include "Gearbox.h"
#include "strategy/StrategySystem.h"
#include "strategy/Strategy.h"
#include "actuators/BinaryActuator.h"
#include "devices/StateDevice.h"
#include "controllers/Controllers.h"

#include "Usage.h"

struct SubSystem2Config {
  wml::Gearbox &gearbox;

  wml::actuators::BinaryActuator &actuator;

  std::string name = "<SubSystem2>";
};

enum class SubSystem2State { kIdle = 0, kIntaking, kOuttaking };

class SubSystem2 : public wml::devices::StateDevice<SubSystem2State>, public wml::StrategySystem {
  public:
  SubSystem2(SubSystem2Config config) : StateDevice(config.name), _config(config) {};

  virtual std::string GetStateString() final;

  void SetIntaking();
  void SetOuttaking();
  void SetIdle();

  SubSystem2Config &GetConfig();
  
  protected:
  virtual void OnStatePeriodic(SubSystem2State state, double dt) override;

  private:
  SubSystem2Config _config;

  wml::Usage<SubSystem2Config>::Scoped _usage{&_config};
};


class SubSystem2ManualStrategy : public wml::Strategy {
 public:
  SubSystem2ManualStrategy(std::string name, SubSystem2 &subsys2, wml::controllers::SmartController &cont1, wml::controllers::SmartController &cont2);

  void OnUpdate(double dt) override;

 private:
  SubSystem2 &_subsys2;
  wml::controllers::SmartController &_cont1, &_cont2;
};
