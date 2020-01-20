#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class BeltIntake {
  public:
    BeltIntake(wml::Gearbox &BeltIntakeMotors, wml::controllers::SmartControllerGroup &contGroup);

    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt);

  private:
    wml::Gearbox &_BeltIntakeMotors;
    wml::controllers::SmartControllerGroup &_contGroup;
};