#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Turret {
	public:
		Turret(wml::Gearbox &RotationalAxis, 
					 wml::Gearbox &VerticalAxis, 
					 wml::Gearbox &FlyWheel, 
					 wml::sensors::LimitSwitch &LeftLimit, 
					 wml::sensors::LimitSwitch &RightLimit, 
					 wml::sensors::LimitSwitch &AngleDownLimit, 
					 wml::controllers::SmartControllerGroup &contGroup, 
					 std::shared_ptr<nt::NetworkTable> &visionTable,
					 std::shared_ptr<nt::NetworkTable> &rotationTable);

		void TeleopOnUpdate(double dt);
		void AutoOnUpdate(double dt);
		void TestOnUpdate(double dt);

		void TuneTurretPID();
		void TuneAnglePID();

		double XAutoAimCalc(double dt, double input);
		double YAutoAimCalc(double dt, double TargetInput);

		void ZeroTurret();
		std::shared_ptr<nt::NetworkTable> table;
		std::shared_ptr<nt::NetworkTable> table_2;


	private:
		wml::Gearbox &_RotationalAxis;
		wml::Gearbox &_VerticalAxis;
		wml::Gearbox &_FlyWheel;

		wml::sensors::LimitSwitch &_LeftLimit;
		wml::sensors::LimitSwitch &_RightLimit;
		wml::sensors::LimitSwitch &_AngleDownLimit;

		wml::controllers::SmartControllerGroup &_contGroup;
		std::shared_ptr<nt::NetworkTable> &_visionTable;
		std::shared_ptr<nt::NetworkTable> &_rotationTable;

		frc::Timer ZeroTimer;

		// PID Calculations X axis (Rotation R)
		double RkP = 0;
		double RkI = 0;
		double RkD = 0;

		double Rerror;

		double Rsum = 0;
		double RpreviousError = 0;
		double Rgoal = 0;

		// PID Calculation Y axis (Angle A)
		double AkP = 0;
		double AkI = 0;
		double AkD = 0;

		double Aerror;

		double Asum = 0;
		double ApreviousError = 0;
		double AGoal = 0;


		// Cam Values
		double imageHeight = 0;
		double imageWidth = 0;
		double targetX = 0;
		double targetY = 0;

		double MinRotation = 0;
		double MaxRotation = 0;
		double MaxAngleRotations = 0;
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