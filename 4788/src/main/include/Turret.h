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

		double XAutoAimCalc(double dt, double input);
		double YAutoAimCalc(double dt, double TargetInput, double EncoderInput, double ImageHeight);

		void ZeroTurret();
		std::shared_ptr<nt::NetworkTable> table;

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

		frc::Timer ZeroTimer;

		// PID Calculations X axis
		double kP = 0;
		double kI = 0;
		double kD = 0;

		double error;

		double sum = 0;
		double previousError = 0;
		double goal = 0;

		// Cam Values
		double imageHeight;
		double imageWidth;
		double targetX;
		double targetY;

		double MinRotation;
		double MaxRotation;
		double MaxAngleRotations;
		double MotorTicks = 2048;

		// Test
		bool turretTest = true;

    bool leftLimitTest = true;
    bool rightLimitTest = true;
    bool leftEncoderTest = true;
    bool rightEncoderTest = true;

		bool angleLimitTest = true;
		bool angleEncoderTet = true;

		bool FlywheelTest = true;

		// Power 
		double RotationPower = 0;
		double AngularPower = 0;
		double FlyWheelPower = 0;
};