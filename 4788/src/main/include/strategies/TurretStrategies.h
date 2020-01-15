#pragma once

#include <string>

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "Turret.h"
#include "RobotMap.h"

struct TurretTeleopConfig {
  double &targetX, &targetY, &imageHeight, &imageWidth;
};

class TurretTeleop : public wml::Strategy {
 public:
  TurretTeleop(std::string name, wml::controllers::SmartControllerGroup &contGroup);

  void OnUpdate(double dt) override;

 private:
  TurretTeleopConfig _config;
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