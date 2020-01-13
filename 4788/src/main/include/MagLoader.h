#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"

class MagLoaderTeleop : public wml::Strategy {
  public:
    MagLoaderTeleop(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};

class MagLoaderAuto : public wml::Strategy {
  public:
    MagLoaderAuto(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};

class MagLoaderTest : public wml::Strategy {
  public:
    MagLoaderTest(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
};