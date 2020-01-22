#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Climber {
  public:
    Climber(wml::actuators::DoubleSolenoid &ClimberActuator, wml::actuators::BinaryServo &ShiftPTO, wml::Gearbox &ExtendElevator, wml::controllers::SmartControllerGroup &contGroup);

    void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::actuators::DoubleSolenoid &_ClimberActuator;
		wml::actuators::BinaryServo &_ShiftPTO;
		wml::Gearbox &_ExtendElevator;
		wml::controllers::SmartControllerGroup &_contGroup;
};