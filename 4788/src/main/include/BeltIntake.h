#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class BeltIntake {
  public:
    BeltIntake(wml::Gearbox &BeltIntakeMotors, 
               wml::actuators::DoubleSolenoid &IntakeDown, 
               wml::controllers::SmartControllerGroup &contGroup);
    
    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt); 

  private:
    wml::Gearbox &_BeltIntakeMotors;
    wml::actuators::DoubleSolenoid &_IntakeDown;
    wml::controllers::SmartControllerGroup &_contGroup;
    //std::shared_ptr<nt::NetworkTable> &_pancakes;


    frc::Timer timer;

    bool ToggleEnabled;
};