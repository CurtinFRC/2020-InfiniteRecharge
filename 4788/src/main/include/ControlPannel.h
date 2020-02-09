#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"


class ControlPannel {
	public:
		ControlPannel(wml::actuators::DoubleSolenoid &ClimberActuator,
									wml::Gearbox &ControlPannelMotor, 
									wml::actuators::DoubleSolenoid &ControlPannelUpSol, 
									wml::controllers::SmartControllerGroup &contGroup,
									std::shared_ptr<nt::NetworkTable> &ControlPannelTable);
		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

	private:
		wml::actuators::DoubleSolenoid &_ClimberActuator;
		wml::Gearbox &_ControlPannelMotor;
		wml::actuators::DoubleSolenoid &_ControlPannelUpSol;
		wml::controllers::SmartControllerGroup &_contGroup;
		std::shared_ptr<nt::NetworkTable> &_ControlPannelTable;

		frc::Timer CringeTimer;

		bool ToggleEnabled;
};