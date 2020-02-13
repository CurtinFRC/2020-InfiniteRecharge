#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"


class ControlPannel {
	public:
		ControlPannel(wml::Gearbox &ControlPannelMotor, 
									wml::Gearbox &ExtendControlPannelMotor, 
									wml::controllers::SmartControllerGroup &contGroup,
									std::shared_ptr<nt::NetworkTable> &ControlPannelTable);
		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::Gearbox &_ControlPannelMotor;
		wml::Gearbox &_ExtendControlPannelMotor;
		wml::controllers::SmartControllerGroup &_contGroup;
		std::shared_ptr<nt::NetworkTable> &_ControlPannelTable;

		frc::Timer CringeTimer;
		double ControlPannelPower = 0;
		double ControlPannelUpPower = 0;

		int TestSelector = 1;

		bool ToggleEnabled;
};