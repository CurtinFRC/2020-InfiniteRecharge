#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class WheelCringeGearBox {
	public:
		WheelCringeGearBox(wml::Gearbox &WheelCringeMotor, wml::controllers::SmartControllerGroup &contGroup);

		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::Gearbox &_WheelCringeMotor;
		wml::controllers::SmartControllerGroup &_contGroup;
};