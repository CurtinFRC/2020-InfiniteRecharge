#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Climber {
  public:
    Climber(wml::actuators::DoubleSolenoid &ClimberActuator, wml::controllers::SmartControllerGroup &contGroup);

    void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::actuators::DoubleSolenoid &_ClimberActuator;
		wml::controllers::SmartControllerGroup &_contGroup;
};