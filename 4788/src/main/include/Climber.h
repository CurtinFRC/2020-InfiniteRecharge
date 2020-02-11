#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Climber {
  public:
    Climber(wml::actuators::DoubleSolenoid &ClimberActuator, 
						wml::Gearbox &ClimberElevator, 
						wml::controllers::SmartControllerGroup &contGroup);		
    void TeleopOnUpdate(double dt);
 		void AutoOnUpdate(double dt);
 		void TestOnUpdate(double dt);

	private:
 		wml::actuators::DoubleSolenoid &_ClimberActuator;
 		wml::Gearbox &_ClimberElevator;
		wml::controllers::SmartControllerGroup &_contGroup;
 	
	 	frc::Timer ClimberTimer;
		double liftSpeed = 0;
		int testType = 1;

 		bool ToggleEnabled;
 };