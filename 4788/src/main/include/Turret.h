#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Turret {
	public:
		Turret(wml::Gearbox &RotationalAxis, wml::Gearbox &VerticalAxis, wml::Gearbox &FlyWheel,  wml::controllers::SmartControllerGroup &contGroup);

		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::Gearbox &_RotationalAxis;
		wml::Gearbox &_VerticalAxis;
		wml::Gearbox &_FlyWheel;
		wml::controllers::SmartControllerGroup &_contGroup;
};