#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class MagLoader {
  public:
    MagLoader(wml::Gearbox &MagazineMotors, 
              frc::AnalogInput &StartMag, 
              frc::AnalogInput &Position1, 
              frc::AnalogInput &Position5, 
              wml::controllers::SmartControllerGroup &contGroup); // also need to add the limit switch & indexing math.

    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt);

  private:
    wml::Gearbox &_MagazineMotors;
    frc::AnalogInput &_StartMag;
    frc::AnalogInput &_Position1;
    frc::AnalogInput &_Position5;
    wml::controllers::SmartControllerGroup &_contGroup;

    bool ToggleEnabled;
    bool MagOverride = false;
    double MagazinePower = 0;

    int testType = 1;
};