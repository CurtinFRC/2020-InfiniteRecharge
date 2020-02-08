#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation,
 							 Gearbox &VerticalAxis, 
							 Gearbox &FlyWheel, 
							 sensors::LimitSwitch &LeftLimit, 
							 sensors::LimitSwitch &RightLimit, 
							 sensors::LimitSwitch &AngleDownLimit, 
							 SmartControllerGroup &contGroup, 
							 std::shared_ptr<nt::NetworkTable> &visionTable) : 
							 
							 _RotationalAxis(Rotation), _VerticalAxis(VerticalAxis), 
							 _FlyWheel(FlyWheel), 
							 _LeftLimit(LeftLimit), 
							 _RightLimit(RightLimit), 
							 _AngleDownLimit(AngleDownLimit), 
							 _contGroup(contGroup), 
							 _visionTable(visionTable) {
	table = _visionTable->GetSubTable("Target");

	imageHeight = table->GetNumber("ImageHeight", 0); 
	imageWidth = table->GetNumber("ImageWidth", 0);
}

void Turret::ZeroTurret() {
	// Zero Encoder on left limit
	ZeroTimer.Start();
	while (_LeftLimit.Get() < 1) {
		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
			_RotationalAxis.transmission->SetVoltage(12 * -0.3);
		} else {
			std::cout << "Turret Zero Timed Out" << std::endl;
			_RotationalAxis.transmission->SetVoltage(0);
			break;
		}
	} 
	_RotationalAxis.encoder->ZeroEncoder();
	MinRotation = (_RotationalAxis.encoder->GetEncoderRotations() + ControlMap::TurretEncoderSafeZone);
	while (_RightLimit.Get() < 1) {
		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
			_RotationalAxis.transmission->SetVoltage(12 * 0.3);
		} else {
			std::cout << "Turret Zero Timed Out" << std::endl;
			_RotationalAxis.transmission->SetVoltage(0);
			break;
		}
	}
	MaxRotation = (_RotationalAxis.encoder->GetEncoderTicks() - ControlMap::TurretEncoderSafeZone);
	while(_AngleDownLimit.Get() < 1) {
		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
			_VerticalAxis.transmission->SetVoltage(12 * 0.2);
		} else {
			_VerticalAxis.transmission->SetVoltage(0);
			std::cout << "Turret Zero Timed Out" << std::endl;
			break;
		}
	}
	ZeroTimer.Stop();
	ZeroTimer.Reset();
	_VerticalAxis.encoder->ZeroEncoder();
	MaxAngleRotations = (_VerticalAxis.encoder->GetEncoderRotations() + ControlMap::TurretEncoderSafeZone);
	_FlyWheel.encoder->ZeroEncoder();
}



double Turret::XAutoAimCalc(double dt, double targetx)  {

	double TurretFullRotation = (ControlMap::TurretEncoderRotations * ControlMap::TurretRatio);
	double Rotations2FOV = (TurretFullRotation/ControlMap::CamFOV);
	double targetXinRotations = targetX * (Rotations2FOV/imageWidth);

	Rgoal = _RotationalAxis.encoder->GetEncoderRotations() + targetXinRotations;
	double input = _RotationalAxis.encoder->GetEncoderRotations();

	// Calculate PID
	Rerror = Rgoal - input;

	double derror = (Rerror - RpreviousError) / dt;
	Rsum = Rsum + Rerror * dt;

	if (Rsum > (imageWidth/2)) {
		Rsum = imageWidth;
	} else if (Rsum < -(imageWidth/2)) {
		Rsum = -imageWidth;
	}

	double output = RkP * Rerror + RkI * Rsum + RkD * derror;

	// Convert to -1 - 1 for motor
	output /= Rotations2FOV;

	table->PutNumber("RoationDError", derror);
	table->PutNumber("RotationError", Rerror);
	table->PutNumber("RotationDelta Time", dt);
	table->PutNumber("RotationOutput", output);

	RpreviousError = Rerror;
	return -output;
}

// Using Setpoints
double Turret::YAutoAimCalc(double dt, double TargetInput) {

	double targetEncoderValue;
	int LowPoint = 10;
	int MaxPoint = 50;
	int PixleMount = 2;

	// Setpoint Selection.
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint1 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint2 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint3 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint4 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint5 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint6 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint7 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint8 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint9 : MaxPoint;
	LowPoint += PixleMount;
	targetEncoderValue = (TargetInput < LowPoint) && (TargetInput > LowPoint + PixleMount) ? ControlMap::AngleSetpoint10 : MaxPoint;
	LowPoint += PixleMount;


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

	table->PutNumber("AngleDError", derror);
	table->PutNumber("AngleError", Aerror);
	table->PutNumber("AngleDelta Time", dt);
	table->PutNumber("AngleOutput", output);

	ApreviousError = Aerror;

	return output;
}

void Turret::TuneTurretPID() {

	if (_contGroup.Get(ControlMap::kpUP, Controller::ONRISE)) {
		RkP += 0.01;
	} else if (_contGroup.Get(ControlMap::kpDOWN, Controller::ONRISE)) {
		RkP -= 0.001;
	} else if (_contGroup.Get(ControlMap::kiUP, Controller::ONRISE)) {
		RkI += 0.001;
	} else if (_contGroup.Get(ControlMap::kiDOWN, Controller::ONRISE)) {
		RkI -= 0.001;
	} else if (_contGroup.Get(ControlMap::kdUP, Controller::ONRISE)) {
		RkD += 0.001;
	}	else if (_contGroup.Get(ControlMap::kdDOWN, Controller::ONRISE)) {
		RkD -= 0.001;
	}

	table->PutNumber("kP", RkP);
	table->PutNumber("kI", RkI);
	table->PutNumber("kD", RkD);
	table->PutNumber("Sum", Rsum);
}

void Turret::TuneAnglePID() {

	if (_contGroup.Get(ControlMap::kpUP, Controller::ONRISE)) {
		AkP += 0.01;
	} else if (_contGroup.Get(ControlMap::kpDOWN, Controller::ONRISE)) {
		AkP -= 0.001;
	} else if (_contGroup.Get(ControlMap::kiUP, Controller::ONRISE)) {
		AkI += 0.001;
	} else if (_contGroup.Get(ControlMap::kiDOWN, Controller::ONRISE)) {
		AkI -= 0.001;
	} else if (_contGroup.Get(ControlMap::kdUP, Controller::ONRISE)) {
		AkD += 0.001;
	}	else if (_contGroup.Get(ControlMap::kdDOWN, Controller::ONRISE)) {
		AkD -= 0.001;
	}

	table->PutNumber("kP", AkP);
	table->PutNumber("kI", AkI);
	table->PutNumber("kD", AkD);
	table->PutNumber("Sum", Asum);
}

void Turret::TeleopOnUpdate(double dt) {

	targetX = table->GetNumber("Target_X", 0)/imageWidth;
	targetY = table->GetNumber("Target_Y", 0)/imageHeight;


	if (ControlMap::TuneTurretPID && ControlMap::TuneAnglePID) {
		std::cout << "Can't Have Both Turret & Angle PID tuning at the same time" << std::endl;
	}	else if (ControlMap::TuneTurretPID) {
		TuneTurretPID();
	} else if (ControlMap::TuneAnglePID) {
		TuneAnglePID();
	}

	
	if (_contGroup.Get(ControlMap::TurretAutoAim)) {
		if (targetX > imageWidth || targetY > imageHeight) {
			std::cout << "Error: Target is artifacting" << std::endl;
		} else {
			RotationPower = XAutoAimCalc(dt, targetX);
			AngularPower = YAutoAimCalc(dt, targetY);
		}
	}	else {
		Asum = 0;
		Rsum = 0;
	}

	// Manual Rotation Control
	RotationPower += std::fabs(_contGroup.Get(ControlMap::TurretManualRotate)) > ControlMap::joyDeadzone ? _contGroup.Get(ControlMap::TurretManualRotate) : 0;

	// Manual Angle Control
	AngularPower += std::fabs(_contGroup.Get(ControlMap::TurretManualAngle)) > ControlMap::joyDeadzone ? _contGroup.Get(ControlMap::TurretManualAngle) : 0;

	// FlyWheel Code
	if ((_contGroup.Get(ControlMap::TurretAutoAim) > ControlMap::triggerDeadzone) && (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > ControlMap::triggerDeadzone)) {
		FlyWheelPower += _FlyWheel.encoder->GetEncoderAngularVelocity() < ControlMap::FlyWheelVelocity ? 0.01 : 0;
	} else if (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > ControlMap::triggerDeadzone) {
		FlyWheelPower = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
	} else {
		FlyWheelPower = 0;
	}

	// Limits Turret Speed
	RotationPower *= ControlMap::MaxTurretSpeed; 
	AngularPower *= ControlMap::MaxTurretAngularSpeed;

	// std::cout << "Flywheel Encoder Velocity " << _FlyWheel.encoder->GetEncoderAngularVelocity() << std::endl;

	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * 0);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);

}

void Turret::AutoOnUpdate(double dt) {

}

void Turret::TestOnUpdate(double dt) {
	if (!leftEncoderTest && !rightEncoderTest) {
		if (turretTest) {
			std::cout << "Turret Test Succesful" << std::endl;
			turretTest = false;
		}
	} else {
		if (leftLimitTest) {

		}
	}

	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * AngularPower);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);
}