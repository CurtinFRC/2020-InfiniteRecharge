#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Climber {
  public:
    Climber(wml::actuators::DoubleSolenoid &ClimberActuator, 
						wml::actuators::DoubleSolenoid &ShiftPTO, 
						wml::Gearbox &ClimberElevatorLeft, 
						wml::Gearbox &ClimberElavatorRight,
						wml::controllers::SmartControllerGroup &contGroup);		
    void TeleopOnUpdate(double dt);
 		void AutoOnUpdate(double dt);
 		void TestOnUpdate(double dt);

	private:
 		wml::actuators::DoubleSolenoid &_ClimberActuator;
 		wml::actuators::DoubleSolenoid &_ShiftPTO;
 		wml::Gearbox &_ClimberElevatorLeft;
		wml::Gearbox &_ClimberElevatorRight;
		wml::controllers::SmartControllerGroup &_contGroup;
 	
	 	frc::Timer ClimberTimer;
		double liftSpeedleft = 0;
  	double liftSpeedright = 0;
		double liftSpeed = 0;
		int testType = 1;

 		bool ToggleEnabled;
 };