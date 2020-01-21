#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation, Gearbox &VerticalAxis, Gearbox &FlyWheel, SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &visionTable) : _RotationalAxis(Rotation), _VerticalAxis(VerticalAxis), _FlyWheel(FlyWheel), _contGroup(contGroup), _visionTable(visionTable) {
	table = _visionTable->GetSubTable("Target");
}


// PID Calculations X axis
double XkP = -0.3;
double XkI = 0;
double XkD = -0.005;

double Xsum = 0;
double XpreviousError = 0;
double Xgoal = 0;


double XAutoAimCalc(double dt, double input)  {
	double error = Xgoal - input;
	double derror = (error - XpreviousError) / dt;
	Xsum = Xsum + error * dt;

	double output = XkP * error + XkI * Xsum + XkD * derror;

	XpreviousError = error;
	return output;
}

// PID Calculations Y axis
double YkP = -0.3;
double YkI = 0;
double YkD = -0.005;

double Ysum = 0;
double YpreviousError = 0;
double Ygoal = 0;

double YAutoAimCalc(double dt, double input) {
	double error = Ygoal - input;
	double derror = (error - YpreviousError) / dt;
	Ysum = Ysum + error * dt;

	double output = YkP * error + YkI * Ysum + YkD * derror;

	YpreviousError = error;
	return output;
}


void Turret::TeleopOnUpdate(double dt) {
	double RotationPower;
	double AngularPower;
	double FlyWheelPower;

	double imageHeight = table->GetNumber("ImageHeight", 0); 
	double imageWidth = table->GetNumber("ImageWidth", 0);

	double targetX = table->GetNumber("Target_X", 0)/imageWidth;
	double targetY = table->GetNumber("Target_Y", 0)/imageHeight;  

	// Turret Manual Rotation
	if (_contGroup.Get(ControlMap::TurretManualRotate) > ControlMap::xboxDeadzone) {
		RotationPower = _contGroup.Get(ControlMap::TurretManualRotate);
	}

	// Turret Manual Angle
	if (_contGroup.Get(ControlMap::TurretManualAngle) > ControlMap::xboxDeadzone) {
		AngularPower = _contGroup.Get(ControlMap::TurretManualAngle);
	}

	// Turret FlyWheel
	if (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > ControlMap::triggerDeadzone) {
		FlyWheelPower = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
	}


	// Turret Auto Aim (Note that we're using Y axis to detect distance. There is a possibility we need a seperate algorithm to adjust angle depending on y axis. Other than zeroing to goal)
	if (_contGroup.Get(ControlMap::TurretAutoAim) > ControlMap::triggerDeadzone) {
		if (targetX > imageWidth || targetY > imageHeight) {
			std::cout << "Error: >> Vision Artifacting Detected" << std::endl; 
		} else {
			RotationPower = XAutoAimCalc(dt, targetX);
			AngularPower = YAutoAimCalc(dt, targetY);
		}
	}
	
	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * AngularPower);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);
}

void Turret::AutoOnUpdate(double dt) {

}

void Turret::TestOnUpdate(double dt) {
	
}


