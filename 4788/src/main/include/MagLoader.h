#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class MagLoader {
  public:
    MagLoader(wml::Gearbox &MagazineMotors, wml::sensors::LimitSwitch &StartMag, wml::sensors::LimitSwitch &Position1, wml::sensors::LimitSwitch &Position5, wml::controllers::SmartControllerGroup &contGroup); // also need to add the limit switch & indexing math.

    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt);

  private:
    wml::Gearbox &_MagazineMotors;
    wml::sensors::LimitSwitch &_StartMag;
    wml::sensors::LimitSwitch &_Position1;
    wml::sensors::LimitSwitch &_Position5;
    wml::controllers::SmartControllerGroup &_contGroup;

    bool ToggleEnabled;
};