#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation, Gearbox &VerticalAxis, Gearbox &FlyWheel, sensors::LimitSwitch &LeftLimit, sensors::LimitSwitch &RightLimit, sensors::LimitSwitch &AngleDownLimit, SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &visionTable) : _RotationalAxis(Rotation), _VerticalAxis(VerticalAxis), _FlyWheel(FlyWheel), _LeftLimit(LeftLimit), _RightLimit(RightLimit), _AngleDownLimit(AngleDownLimit), _contGroup(contGroup), _visionTable(visionTable) {
	table = _visionTable->GetSubTable("Target");
}

void Turret::ZeroTurret() {
	while (!_LeftLimit.Get()) {
		_RotationalAxis.transmission->SetVoltage(12 * -0.3);
	} 
	_RotationalAxis.encoder->ZeroEncoder();
	while (!_RightLimit.Get()) {
		_RotationalAxis.transmission->SetVoltage(12 * 0.3);
	}
	MaxRotationTicks = _RotationalAxis.encoder->GetEncoderTicks();
	while(!_AngleDownLimit.Get()) {
		_VerticalAxis.transmission->SetVoltage(12 * 0.2);
	}
	_VerticalAxis.encoder->ZeroEncoder();
	_FlyWheel.encoder->ZeroEncoder();
}


// PID Calculations X axis
double XkP = 0.25;
double XkI = 0.0002;
double XkD = 0.00003;

double Xsum = 0;
double XpreviousError = 0;
double Xgoal = 0;

double FOV = 60;

// Turret FOV 60 degrees



double Turret::XAutoAimCalc(double dt, double input)  {
	double error = Xgoal - input;
	double derror = (error - XpreviousError) / dt;
	Xsum = (Xsum>1000) ? 1000 : Xsum + error * dt;
	std::cout << "XSum = " << Xsum << std::endl;
	table->PutNumber("XSum", Xsum);

	double output = XkP * error + XkI * Xsum + XkD * derror;

	XpreviousError = error;
	return -output;
}

double Turret::YAutoAimCalc(double dt, double TargetInput, double EncoderInput, double ImageHeight) {

	double output = 0;

	
	
	/**
	 * We need the angle to adjust to a certain angle depending on the distance.
	 * The target is at a set height. So we just need the angle to change depending on the Y value
	 * The Camera isn't placed on the moving part of the angle. (Mostly because we don't want it to go to zero, we want it to go to curve the ball trajectory)
	 * The best Way to do this (From Jaci's experience) is to get the encoder/angle at certain distances of the target, then depending on those set points create a program
	 * that also calclates the inbetweens. Should be easy right...
	 * 
	 * We need about three set points which will give us our main algorithm
	 * Set point 1 (Put the robot as far back as it can with the ball going into the goal)
	 * Set point 2 (The closest the robot can be and still shoot into the goal)
	 * Set point 3 (This is the middle point between the furthest and closest)
	 * 
	 * After this we should be able to get an algorithm using the 3 points to adjust the angle for everything in between as well.
	*/


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
	
	if (_contGroup.Get(ControlMap::TurretAutoAim) > ControlMap::triggerDeadzone) {
		if (targetX > imageWidth || targetY > imageHeight) {
			std::cout << "Error: Target is artifacting" << std::endl;
		} else {
			RotationPower = XAutoAimCalc(dt, targetX);
		}
	}

	if (_contGroup.Get(ControlMap::TurretManualRotate) > ControlMap::joyDeadzone) {
		RotationPower = _contGroup.Get(ControlMap::TurretManualRotate);
	}

	if (_contGroup.Get(ControlMap::TurretManualRotate) < -ControlMap::joyDeadzone) {
		RotationPower = _contGroup.Get(ControlMap::TurretManualRotate);
	}
	
	_RotationalAxis.transmission->SetVoltage(12 * RotationPower);
	_VerticalAxis.transmission->SetVoltage(12 * AngularPower);
	_FlyWheel.transmission->SetVoltage(12 * FlyWheelPower);

	std::cout << "Rotation Power " << RotationPower << std::endl;

	// std::cout << "FlyWheel Encoder " << _FlyWheel.encoder->GetEncoderTicks() << std::endl;
}

void Turret::AutoOnUpdate(double dt) {

}

void Turret::TestOnUpdate(double dt) {
	
}


