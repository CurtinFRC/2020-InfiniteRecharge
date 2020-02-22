#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class MagLoader {
  public:
    MagLoader(wml::Gearbox &MagazineMotors, 
              frc::AnalogInput &StartMag, 
              frc::AnalogInput &Position1, 
              frc::AnalogInput &Position5, 
              wml::controllers::SmartControllerGroup &contGroup);

    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt);

  private:
    wml::Gearbox &_MagazineMotors;
    frc::AnalogInput &_StartMag;
    frc::AnalogInput &_Position1;
    frc::AnalogInput &_Position5;
    wml::controllers::SmartControllerGroup &_contGroup;

    // Auto Ball detection (Magazine control)
    void AutoMag();

    bool ToggleEnabled;
    bool MagOverride = false;
    double MagazinePower = 0;
    int MagStop = 1;
    
    int testType = 1;
};