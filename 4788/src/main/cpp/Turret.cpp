#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Turret::Turret(Gearbox &Rotation, Gearbox &VerticalAxis, Gearbox &FlyWheel, SmartControllerGroup &contGroup) : _RotationalAxis(Rotation), _VerticalAxis(VerticalAxis), _FlyWheel(FlyWheel), _contGroup(contGroup) {}

void Turret::TeleopOnUpdate(double dt) {
	double RotationPower;
	double AngularPower;
	double FlyWheelPower;

	if (_contGroup.Get(ControlMap::TurretManualRotate) > ControlMap::xboxDeadzone) {
		RotationPower = _contGroup.Get(ControlMap::TurretManualRotate);
	}

	if (_contGroup.Get(ControlMap::TurretManualAngle) > ControlMap::xboxDeadzone) {
		AngularPower = _contGroup.Get(ControlMap::TurretManualAngle);
	}

	if (_contGroup.Get(ControlMap::TurretFlyWheelSpinUp) > ControlMap::triggerDeadzone) {
		FlyWheelPower = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
	}
	
	_RotationalAxis.transmission->SetVoltage(RotationPower);
	_VerticalAxis.transmission->SetVoltage(AngularPower);
	_FlyWheel.transmission->SetVoltage(FlyWheelPower);
}