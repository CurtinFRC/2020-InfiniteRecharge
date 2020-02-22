#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class Turret {
	public:
		Turret(wml::Gearbox &RotationalAxis, 
					 wml::Gearbox &VerticalAxis, 
					 wml::Gearbox &FlyWheel, 
					 wml::sensors::BinarySensor &LeftLimit, 
					 wml::sensors::BinarySensor &RightLimit, 
					 wml::sensors::BinarySensor &AngleDownLimit, 
					 wml::controllers::SmartControllerGroup &contGroup, 
					 std::shared_ptr<nt::NetworkTable> &visionTable,
					 std::shared_ptr<nt::NetworkTable> &rotationTable, 
					 bool &FlyWheelToggle,
					 bool &TurretToggle, 
					 int &autoSelector, 
					 bool &StartDoComplete,
					 bool &strt,
					 bool &p1,
					 bool &p2,
					 bool &p3,
					 bool &end);

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

		wml::sensors::BinarySensor &_LeftLimit;
		wml::sensors::BinarySensor &_RightLimit;
		wml::sensors::BinarySensor &_AngleDownLimit;

		wml::controllers::SmartControllerGroup &_contGroup;
		std::shared_ptr<nt::NetworkTable> &_visionTable;
		std::shared_ptr<nt::NetworkTable> &_rotationTable;

		bool &_FlyWheelToggle;
		bool &_TurretToggle;
		int &_autoSelector;
		bool &_StartDoComplete;
		bool &_strt;
		bool &_p1;
		bool &_p2;
		bool &_p3;
		bool &_end;

		// Timeout Timer
		frc::Timer ZeroTimer;

		bool TuningTurret = false;

		// Backend Functions
		double SetPointSelection(double LowPoint, double MaxPoint, double PixleAmount, double TargetInput);
		void TurretZeroLeft(double Time);
		void TurretZeroRight(double Time);
		void TurretZeroAngle(double Time);
		void ContFlywheelFeedback();
		void FlyWheelAutoSpinup();
		void FlyWheelManualSpinup();
		void PIDTuner();
		void AutoAimToFire();
		void TurretSearchForTarget();

		// PID Calculations X axis (Rotation R)
		double RkP = 1;
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

		//auto 
		int AutoTurretSwitcher = 1; // I didnt really know what to call it
		int TurretAutoSelection = 0; //tells the turret which case selection it's in
		int BallTime3Shoot = 1.5;
		int BallTime5Shoot = 2.5;
		int SpinUpTime = 1;
		int Ball3Shoot = BallTime3Shoot + SpinUpTime; //time to shoot 3 balls
		int Ball5Shoot = BallTime5Shoot + SpinUpTime; //shoots 5 balls 
		frc::Timer timer;
};