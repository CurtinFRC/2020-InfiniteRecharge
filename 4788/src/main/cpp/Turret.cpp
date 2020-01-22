#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation, Gearbox &VerticalAxis, Gearbox &FlyWheel, sensors::LimitSwitch &LeftLimit, sensors::LimitSwitch &RightLimit, sensors::LimitSwitch &AngleDownLimit, SmartControllerGroup &contGroup, std::shared_ptr<nt::NetworkTable> &visionTable) : _RotationalAxis(Rotation), _VerticalAxis(VerticalAxis), _FlyWheel(FlyWheel), _LeftLimit(LeftLimit), _RightLimit(RightLimit), _AngleDownLimit(AngleDownLimit), _contGroup(contGroup), _visionTable(visionTable) {
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

double YAutoAimCalc(double dt, double TargetInput, double EncoderInput, double ImageHeight) {

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

	if (_LeftLimit.Get()) {
		RotationPower = 0;
	} else if (_RightLimit.Get()) {
		RotationPower = 0;
	} else if (_AngleDownLimit.Get()) {
		AngularPower = 0;
	} else {

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
			if (_LeftLimit.Get()) {
				std::cout << "Left Limit Hit" << std::endl;
				while (targetX < 0) {
					RotationPower = 0.5;
				}
			} else if (_RightLimit.Get()) {
				std::cout << "Right Limit Hit" << std::endl;
				while (targetX > 0) {
					RotationPower = -0.5;
				}
			} else if (_AngleDownLimit.Get()) {
				std::cout << "Angle Limit Hit" << std::endl;
				AngularPower = 0;
			} else {
				if (targetX > imageWidth || targetY > imageHeight) {
					std::cout << "Error: >> Vision Artifacting Detected" << std::endl; 
				} else {
					RotationPower = XAutoAimCalc(dt, targetX);
					AngularPower = YAutoAimCalc(dt, targetY, _VerticalAxis.encoder->GetEncoderTicks(), imageHeight);
				}
			}
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


