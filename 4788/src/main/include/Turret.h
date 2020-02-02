#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Turret {
	public:
		Turret(wml::Gearbox &RotationalAxis, wml::Gearbox &VerticalAxis, wml::Gearbox &FlyWheel, wml::sensors::LimitSwitch &LeftLimit, wml::sensors::LimitSwitch &RightLimit, wml::sensors::LimitSwitch &AngleDownLimit, wml::controllers::SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &visionTable);

		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

		void TuneTurretPID();

		double XAutoAimCalc(double dt);
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

		// PID Calculations X axis
		double kP = 0;
		double kI = 0;
		double kD = 0;

		double sum = 0;
		double previousError = 0;
		double goal = 0;

		// Cam Values
		double imageHeight;
		double imageWidth;
		double targetX;
		double targetY;

		double ticksToTargetX;

		// Turret Cam FOV/Turret Gear Values
		double CamFOV = 60; // Degrees
		double TurretLargeGearDiameter = 330; // Mills
		double TurretSmallGearDiameter = 47.75;
		double TurretMotorGearRatio = 10; // Ratio
		double TurretMotorGearRatioTo = 1;

		double TicksPerTurretRotation;
		double TicksPerCamFOV;


		double MaxRotationTicks;
		double MaxAngleTicks;
		double MotorTicks = 2048;
};