#pragma once

#include <string>

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "Turret.h"
#include "RobotMap.h"

class TurretTeleop : public wml::Strategy {
  public:
    TurretTeleop(std::string name, wml::Turret &turret, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::Turret &_turret;
    wml::controllers::SmartControllerGroup &_contGroup;
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