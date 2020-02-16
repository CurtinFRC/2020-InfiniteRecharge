#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation,
 							 Gearbox &VerticalAxis, 
							 Gearbox &FlyWheel, 
							 sensors::BinarySensor &LeftLimit, 
							 sensors::BinarySensor &RightLimit, 
							 sensors::BinarySensor &AngleDownLimit, 
							 SmartControllerGroup &contGroup, 
							 std::shared_ptr<nt::NetworkTable> &visionTable,
							 std::shared_ptr<nt::NetworkTable> &rotationTable, 
							 bool &TurretDisable) : 

							 
							 _RotationalAxis(Rotation),
						   _VerticalAxis(VerticalAxis), 
							 _FlyWheel(FlyWheel), 
							 _LeftLimit(LeftLimit), 
							 _RightLimit(RightLimit), 
							 _AngleDownLimit(AngleDownLimit), 
							 _contGroup(contGroup), 
							 _visionTable(visionTable),
							 _rotationTable(rotationTable),
							 _TurretDisable(TurretDisable){
	table = _visionTable->GetSubTable("Target");
	table_2 =  _rotationTable->GetSubTable("turretRotation");

	imageHeight = table->GetNumber("ImageHeight", 0); 
	imageWidth = table->GetNumber("ImageWidth", 0);
}

void Turret::ZeroTurret() {
	// Zero Encoder on left limit
	ZeroTimer.Start();

	// Get Left Limit
	Turret::TurretZeroLeft(ZeroTimer.Get());

	// Minimum Rotations
	MinRotation = (_RotationalAxis.encoder->GetEncoderRotations() + ControlMap::TurretEncoderSafeZone);
	
	// Get Right Limit
	Turret::TurretZeroRight(ZeroTimer.Get());

	// Get Max Rotations
	MaxRotation = (_RotationalAxis.encoder->GetEncoderTicks() - ControlMap::TurretEncoderSafeZone);

	// Get Angle Limit
	Turret::TurretZeroAngle(ZeroTimer.Get());
	
	// Reset Timers
	ZeroTimer.Stop();
	ZeroTimer.Reset();

	// Maxed Vertical Axis & Zero Flywheel
	MaxAngleRotations = (_VerticalAxis.encoder->GetEncoderRotations() + ControlMap::TurretEncoderSafeZone);
	_FlyWheel.encoder->ZeroEncoder();
}

// Using Setpoints
double Turret::YAutoAimCalc(double dt, double TargetInput) {

	double targetEncoderValue;
	int LowPoint = 10;
	int MaxPoint = 50;
	int PixleAmount = 2;

	// Setpoint Selection.
	targetEncoderValue = SetPointSelection(LowPoint, MaxPoint, PixleAmount, TargetInput);


	// Calculate PID
	double input = _RotationalAxis.encoder->GetEncoderRotations();
	Aerror = targetEncoderValue - input;

	double derror = (Aerror - ApreviousError) / dt;
	Asum = Asum + Aerror * dt;

	if (Asum > (imageHeight/2)) {
		Asum = imageHeight;
	} else if (Asum < -(imageHeight/2)) {
		Asum = -imageHeight;
	}

	
	double output = AkP * Aerror + AkI * Asum + AkD * derror;

	// Convert to -1 - 1 for motor
	output /= ControlMap::MaxAngleEncoderRotations;

	// Temp Values
	table->PutNumber("AngleDError", derror);
	table->PutNumber("AngleError", Aerror);
	table->PutNumber("AngleDelta Time", dt);
	table->PutNumber("AngleOutput", output);

	ApreviousError = Aerror;

	return output;
}

void Turret::TeleopOnUpdate(double dt) {

	targetX = table->GetNumber("Target_X", 0)/imageWidth;
	targetY = table->GetNumber("Target_Y", 0)/imageHeight;

	// Tune Turret PID (If active)
	PIDTuner();
	

	if (_contGroup.Get(ControlMap::TurretAutoAim)) {
		if (targetX > imageWidth || targetY > imageHeight) {
			std::cout << "Error: Target is artifacting" << std::endl;
		} else {
			RotationPower = XAutoAimCalc(dt, targetX);
			AngularPower = YAutoAimCalc(dt, targetY);
		}
	}


	if (!_TurretDisable) {
		// Manual Angle Control
		AngularPower += std::fabs(_contGroup.Get(ControlMap::TurretManualAngle)) > ControlMap::joyDeadzone ? _contGroup.Get(ControlMap::TurretManualAngle) : 0;

		// Manual Rotation Control
		RotationPower += std::fabs(_contGroup.Get(ControlMap::TurretManualRotate)) > ControlMap::joyDeadzone ? _contGroup.Get(ControlMap::TurretManualRotate) : 0;
	} 

	// FlyWheel Code
	if ((_contGroup.Get(ControlMap::TurretAutoAim) > ControlMap::triggerDeadzone) && (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > ControlMap::triggerDeadzone)) {
		FlyWheelPower += _FlyWheel.encoder->GetEncoderAngularVelocity() < ControlMap::FlyWheelVelocity ? 0.01 : 0;
	} else if (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > ControlMap::triggerDeadzone) {
		FlyWheelPower = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
	} else {
		FlyWheelPower = 0;
	}

	// Flywheel Feedback
	ContFlywheelFeedback();

	// Limits Turret Speed
	RotationPower *= ControlMap::MaxTurretSpeed; 
	AngularPower *= ControlMap::MaxTurretAngularSpeed;

	table_2->PutNumber("Turret_Min", MinRotation);
	table_2->PutNumber("Turret_Max", MaxRotation);

	// temp
	// std::cout << "Flywheel Encoder Velocity " << _FlyWheel.encoder->GetEncoderAngularVelocity() << std::endl;

	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * 0);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);

}

void Turret::AutoOnUpdate(double dt) {

}

// @TODO Turret Test

void Turret::TestOnUpdate(double dt) {

	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * AngularPower);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);
}