#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

class IntakeTeleop : public wml::Strategy {
  public:
    IntakeTeleop(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};

class IntakeAuto : public wml::Strategy {
  public:
    IntakeAuto(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};

class IntakeTest : public wml::Strategy {
  public:
    IntakeTest(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};