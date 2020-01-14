#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "RobotMap.h"

class TurretTeleop : public wml::Strategy {
  public:
    TurretTeleop(std::string name, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::controllers::SmartControllerGroup &_contGroup;
    RobotMap robotMap;
};

class TurretAuto : public wml::Strategy {
  public:
    TurretAuto(std::string name);

    void OnUpdate(double dt) override;
};

class TurretTest : public wml::Strategy {
  public: 
    TurretTest(std::string name);

    void OnUpdate(double dt) override;
};