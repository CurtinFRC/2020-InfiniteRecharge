#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation, Gearbox &VerticalAxis, Gearbox &FlyWheel, sensors::LimitSwitch &LeftLimit, sensors::LimitSwitch &RightLimit, sensors::LimitSwitch &AngleDownLimit, SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &visionTable) : _RotationalAxis(Rotation), _VerticalAxis(VerticalAxis), _FlyWheel(FlyWheel), _LeftLimit(LeftLimit), _RightLimit(RightLimit), _AngleDownLimit(AngleDownLimit), _contGroup(contGroup), _visionTable(visionTable) {
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
	while (_RightLimit.Get() < 1) {
		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
			_RotationalAxis.transmission->SetVoltage(12 * 0.3);
		} else {
			std::cout << "Turret Zero Timed Out" << std::endl;
			_RotationalAxis.transmission->SetVoltage(0);
			break;
		}
	}
	MaxRotationTicks = _RotationalAxis.encoder->GetEncoderTicks();
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
	_FlyWheel.encoder->ZeroEncoder();
}



double Turret::XAutoAimCalc(double dt, double input)  {

	


	// Calculate PID
	error = goal - input;

	double derror = (error - previousError) / dt;
	sum = sum + error * dt;

	if (sum > (imageWidth/2)) {
		sum = imageWidth;
	} else if (sum < -(imageWidth/2)) {
		sum = -imageWidth;
	}

	double output = kP * error + kI * sum + kD * derror;

	table->PutNumber("DError", derror);
	table->PutNumber("Error", error);
	table->PutNumber("Delta Time", dt);
	table->PutNumber("Output", output);

	previousError = error;
	return -output;
}

double Turret::YAutoAimCalc(double dt, double TargetInput, double EncoderInput, double ImageHeight) {

	double output = 0;


	return output;
}

void Turret::TuneTurretPID() {

		if (_contGroup.Get(ControlMap::kpUP, Controller::ONRISE)) {
		kP = kP + 0.01;
	} else if (_contGroup.Get(ControlMap::kpDOWN, Controller::ONRISE)) {
		kP = kP - 0.001;
	} else if (_contGroup.Get(ControlMap::kiUP, Controller::ONRISE)) {
		kI = kI + 0.001;
	} else if (_contGroup.Get(ControlMap::kiDOWN, Controller::ONRISE)) {
		kI = kI - 0.001;
	} else if (_contGroup.Get(ControlMap::kdUP, Controller::ONRISE)) {
		kD = kD + 0.001;
	}	else if (_contGroup.Get(ControlMap::kdDOWN, Controller::ONRISE)) {
		kD = kD - 0.001;
	}

	table->PutNumber("kP", kP);
	table->PutNumber("kI", kI);
	table->PutNumber("kD", kD);

}

void Turret::TeleopOnUpdate(double dt) {

	targetX = table->GetNumber("Target_X", 0)/imageWidth;
	targetY = table->GetNumber("Target_Y", 0)/imageHeight;


	if (ControlMap::TuneTurretPID) {
		TuneTurretPID();
	}

	
	if (_contGroup.Get(ControlMap::TurretAutoAim) > ControlMap::triggerDeadzone) {
		if (targetX > imageWidth || targetY > imageHeight) {
			std::cout << "Error: Target is artifacting" << std::endl;
		} else {
			RotationPower = XAutoAimCalc(dt, targetX);
		}
	}	else {
		sum = 0;
	}
	table->PutNumber("Sum", sum);

	if (_contGroup.Get(ControlMap::TurretManualRotate) > ControlMap::joyDeadzone) {
		RotationPower = _contGroup.Get(ControlMap::TurretManualRotate);
		RotationPower = RotationPower/6;
	}

	if (_contGroup.Get(ControlMap::TurretManualRotate) < -ControlMap::joyDeadzone) {
		RotationPower = _contGroup.Get(ControlMap::TurretManualRotate);
		RotationPower = RotationPower/6;
	}

	if (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > 0.1) {
		FlyWheelPower = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
	} else {
		FlyWheelPower = 0;
	}

	if (_contGroup.Get(ControlMap::TurretFire)) {
		AngularPower = 1;
	} else {
		AngularPower = 0;
	}
	

	// Motor DeadBand Calc
	float ForwardDB = 0.14; // actually 0.118
	float ReverseDB = 0.16; // actually 0.138
	if(RotationPower > 0.01) {
		RotationPower = (1-ForwardDB)*RotationPower + ForwardDB;
	} 
	if(RotationPower < -0.01) {
		RotationPower = (1-ReverseDB)*RotationPower - ReverseDB;
	} 

	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * 0);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);

	// std::cout << "FlyWheel Encoder " << _FlyWheel.encoder->GetEncoderTicks() << std::endl;
	table->PutNumber("Rotation Power", RotationPower);
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


