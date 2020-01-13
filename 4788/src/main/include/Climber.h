#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

class ClimberTeleop : public wml::Strategy {
  public:
    ClimberTeleop(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};

class ClimberAuto : public wml::Strategy {
  public:
    ClimberAuto(std::string name);

    void OnUpdate(double dt) override;
};

class ClimberTest : public wml::Strategy {
  public:
    ClimberTest(std::string name);

    void OnUpdate(double dt) override;
};