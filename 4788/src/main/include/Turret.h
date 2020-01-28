#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Turret {
	public:
		Turret(wml::Gearbox &RotationalAxis, wml::Gearbox &VerticalAxis, wml::Gearbox &FlyWheel, wml::sensors::LimitSwitch &LeftLimit, wml::sensors::LimitSwitch &RightLimit, wml::sensors::LimitSwitch &AngleDownLimit, wml::controllers::SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &visionTable);

		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

		double XAutoAimCalc(double dt, double input);
		double YAutoAimCalc(double dt, double TargetInput, double EncoderInput, double ImageHeight);

		void ZeroTurret();

	private:
		wml::Gearbox &_RotationalAxis;
		wml::Gearbox &_VerticalAxis;
		wml::Gearbox &_FlyWheel;

		wml::sensors::LimitSwitch &_LeftLimit;
		wml::sensors::LimitSwitch &_RightLimit;
		wml::sensors::LimitSwitch &_AngleDownLimit;
		// Might add up limit if necessart


		wml::controllers::SmartControllerGroup &_contGroup;
		std::shared_ptr<nt::NetworkTable> &_visionTable;
		std::shared_ptr<nt::NetworkTable> table;

		double MaxRotationTicks;
		double MaxAngleTicks;
};