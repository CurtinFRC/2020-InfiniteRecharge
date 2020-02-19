#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class BeltIntake {
  public:
    BeltIntake(wml::Gearbox &BeltIntakeMotors, 
               wml::actuators::DoubleSolenoid &IntakeDown, 
               wml::controllers::SmartControllerGroup &contGroup,
               int &autoSelector,
               bool &StartDoComplete,
               bool &strt,
               bool &p1,
               bool &p2,
               bool &p3,
               bool &end,
               bool &FlyWheelToggle,
               bool &TurretToggle);
    
    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt); 

  private:
    wml::Gearbox &_BeltIntakeMotors;
    wml::actuators::DoubleSolenoid &_IntakeDown;
    wml::controllers::SmartControllerGroup &_contGroup;
    int &_autoSelector;
    bool &_StartDoComplete;
    bool &_strt;
    bool &_p1;
    bool &_p2;
    bool &_p3;
    bool &_end;
    bool IntakeStop = false;

    bool &_FlyWheelToggle;
    bool &_TurretToggle;


    frc::Timer timer;
    double IntakePower = 0;
    int TestType = 1;
    int timeout = 3;

    bool ToggleEnabled = false;
    bool ToggleIntakeOn = false;
};