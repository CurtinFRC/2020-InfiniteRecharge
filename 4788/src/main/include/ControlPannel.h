#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"


class ControlPannel {
	public:
		ControlPannel(wml::Gearbox &ControlPannelMotor, wml::actuators::DoubleSolenoid &PannelPnSol, wml::controllers::SmartControllerGroup &contGroup);

		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::Gearbox &_ControlPannelMotor;
		wml::actuators::DoubleSolenoid &_PannelPnSol;
		wml::controllers::SmartControllerGroup &_contGroup;
		frc::Timer timer;
};