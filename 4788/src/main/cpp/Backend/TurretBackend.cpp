#include "Turret.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

// Bulk of the code that is used but never looked at... unless you look at it

void Turret::InitializeSetPoints() {
	// I'm going top to bottom
	AngleSetPoint[0] = ControlMap::AngleSetpoint1;
	AngleSetPoint[50] = ControlMap::AngleSetpoint2;
	AngleSetPoint[100] = ControlMap::AngleSetpoint3;
	AngleSetPoint[150] = ControlMap::AngleSetpoint4;
	AngleSetPoint[200] = ControlMap::AngleSetpoint5;
	AngleSetPoint[250] = ControlMap::AngleSetpoint6;
	AngleSetPoint[300] = ControlMap::AngleSetpoint7;
	AngleSetPoint[350] = ControlMap::AngleSetpoint8;
	AngleSetPoint[400] = ControlMap::AngleSetpoint9;
	AngleSetPoint[450] = ControlMap::AngleSetpoint10;
}

// Distance Setpoints for Turret Angle
double Turret::SetPointSelection(double TargetInput) {
  double targetEncoderValue;
	int multiple = 50; // How many pixels to skip
	// Skip a few pixels to make it easier
	if ((int)targetY % multiple == 0) {
		targetEncoderValue = AngleSetPoint[(int)targetY];
	} else {
		int nearestSetpoint = ((targetY+multiple/2)/multiple) * multiple;
		targetEncoderValue = AngleSetPoint[nearestSetpoint];
	}
	std::cout << "Target Encoder Value: " << targetEncoderValue << std::endl;
  return targetEncoderValue;
}


// Function called in auto (Aims to fire)
void Turret::AutoAimToFire(double dt) {
 
	FlyWheelAutoSpinup();

	RotationPower = XAutoAimCalc(dt, targetX);
	AngularPower = YAutoAimCalc(dt, targetY);

	_RotationalAxis.transmission->SetVoltage(12 * FlyWheelPower);
	_VerticalAxis.transmission->SetVoltage(12 * AngularPower);

}

void Turret::FlyWheelAutoSpinup() {
	FlyWheelPower += _FlyWheel.encoder->GetEncoderAngularVelocity() < ControlMap::FlyWheelVelocity ? 0.05 : 0;
	if (_FlyWheel.encoder->GetEncoderAngularVelocity() <= ControlMap::FlyWheelVelocity) {
		ReadyToFire = true;
	} else {
		ReadyToFire = false;
	}
}



// Turret Search Program
bool SearchSwitcher = false;
void Turret::TurretSearchForTarget() {
	//@TODO CJ
	if (SearchSwitcher) {
		if (_RotationalAxis.encoder->GetEncoderRotations() > Turret::MinRotation) {
			RotationPower = -0.2;
		} else {
			RotationPower = 0;
			SearchSwitcher = false;
		}
	}	else if (!SearchSwitcher) {
		if (_RotationalAxis.encoder->GetEncoderRotations() < Turret::MaxAngleRotations) {
			RotationPower = 0.2;
		} else {
			RotationPower = 0;
			SearchSwitcher = true;
		}
	}

}


// Using Setpoints
double Turret::YAutoAimCalc(double dt, double TargetInput) {
	double targetEncoderValue;

	// Setpoint Selection.
	targetEncoderValue = SetPointSelection(TargetInput);


	// Calculate PID
	double input = _VerticalAxis.encoder->GetEncoderRotations();
	Aerror = targetEncoderValue - input;

	double derror = (Aerror - ApreviousError) / dt;
	Asum = Asum + Aerror * dt;

	if (Asum > (imageHeight/2)) {
		Asum = imageHeight;
	} else if (Asum < -(imageHeight/2)) {
		Asum = -imageHeight;
	}

	
	double output = AkP * Aerror + AkI * Asum + AkD * derror;

	// Temp Values
	table->PutNumber("AngleDError", derror);
	table->PutNumber("AngleError", Aerror);
	table->PutNumber("AngleDelta Time", dt);
	table->PutNumber("AngleOutput", output);

	ApreviousError = Aerror;

	return output;
}

// Query The camera
double Turret::TurretQuery(double Rgoal) {
	double TurretFullRotation = (ControlMap::TurretRatio * ControlMap::TurretGearBoxRatio);
	Rotations2FOV = (TurretFullRotation/ControlMap::CamFOV);
	double targetXinRotations = targetX * (Rotations2FOV/imageWidth);

	if (cameraSyncTimer.Get() > 2) {
		Rgoal = _RotationalAxis.encoder->GetEncoderRotations() + targetXinRotations;
		cameraSyncTimer.Reset();
	}

	return Rgoal;
}

// Schedule Gains
double Turret::ScheduleGains(double dt) {
	if (abs(targetX) < (abs(imageWidth)/8)) {
		dt = 0.5; // Make accumulator awesome baby
		kP = &RkP3;
		kI = &RkI3;
		kD = &RkD3;
		GainsSchedule2 = true;
	} else if (abs(targetX) < (abs(imageWidth)/6)) {
		kP = &RkP2;
		kI = &RkI2;
		kD = &RkD2;
		GainsSchedule2 = true;
	} else {
		kP = &RkP;
		kI = &RkI;
		kD = &RkD;
		GainsSchedule2 = false;
	}
	return dt;
}

double RotGoal = 0;
// X Auto Aim Algorithm
double Turret::XAutoAimCalc(double dt, double targetx)  {
	double TurretFullRotation = (ControlMap::TurretRatio * ControlMap::TurretGearBoxRatio);
	Rotations2FOV = (TurretFullRotation/ControlMap::CamFOV);
	double targetXinRotations = targetX * (Rotations2FOV/imageWidth);

	RotGoal = _RotationalAxis.encoder->GetEncoderRotations() + targetXinRotations;

	// RotGoal = TurretQuery(RotGoal);
	dt = ScheduleGains(dt);
	double input = _RotationalAxis.encoder->GetEncoderRotations();

	// Calculate PID
	Rerror = RotGoal - input;

	double derror = (Rerror - RpreviousError) / dt;
	Rsum = Rsum + Rerror * dt;

	double output;
	output = *kP * Rerror + *kI * Rsum + *kD * derror;

	table->PutBoolean("Schedule 2 electric boogaloo", GainsSchedule2);


	// Convert to -1 - 1 for motor (Don't have to do this. Just makes my life easier)
	// output = output/Rotations2FOV;

	table->PutNumber("RoationDError", derror);
	table->PutNumber("RotationError", Rerror);
	table->PutNumber("RotationDelta Time", dt);
	table->PutNumber("RotationOutput", output);

	RpreviousError = Rerror;
	return output;
}


// Tuning Functions

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

// Turret PID Tuning
void Turret::TuneTurretPID() {
	if (GainsSchedule2) {
		if (_contGroup.Get(ControlMap::kpUP, Controller::ONRISE)) {
			RkP2 += 0.01;
		} else if (_contGroup.Get(ControlMap::kpDOWN, Controller::ONRISE)) {
			RkP2 -= 0.01;
		} else if (_contGroup.Get(ControlMap::kiUP, Controller::ONRISE)) {
			RkI2 += 0.001;
		} else if (_contGroup.Get(ControlMap::kiDOWN, Controller::ONRISE)) {
			RkI2 -= 0.001;
		} else if (_contGroup.Get(ControlMap::kdUP, Controller::ONRISE)) {
			RkD2 += 0.001;
		}	else if (_contGroup.Get(ControlMap::kdDOWN, Controller::ONRISE)) {
			RkD2 -= 0.001;
		}

		table->PutNumber("kP", RkP2);
		table->PutNumber("kI", RkI2);
		table->PutNumber("kD", RkD2);
		table->PutNumber("Sum", Rsum);

	} else {
		if (_contGroup.Get(ControlMap::kpUP, Controller::ONRISE)) {
			RkP += 0.01;
		} else if (_contGroup.Get(ControlMap::kpDOWN, Controller::ONRISE)) {
			RkP -= 0.01;
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
}

// Zeroing To Left
void Turret::TurretZeroLeft(double Time) {
  while (_LeftLimit.Get() < 1) {
		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
			_RotationalAxis.transmission->SetVoltage(12 * -0.3);
		} else {
			std::cout << "Turret Zero Timed Out" << std::endl;
			_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 1);
			_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 1);
			_RotationalAxis.transmission->SetVoltage(0);
			break;
		}
	} 
  _RotationalAxis.encoder->ZeroEncoder();
}

// Zeroing To Right
// void Turret::TurretZeroRight(double Time) {
//   while (_RightLimit.Get() < 1) {
// 		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
// 			_RotationalAxis.transmission->SetVoltage(12 * 0.3);
// 		} else {
// 			std::cout << "Turret Zero Timed Out" << std::endl;
// 			_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 1);
// 			_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 1);
// 			_RotationalAxis.transmission->SetVoltage(0);
// 			break;
// 		}
// 	}
// }

// Zero Angle
void Turret::TurretZeroAngle(double Time) {
  while(_AngleDownLimit.Get() < 1) {
		if (ZeroTimer.Get() < ControlMap::TurretZeroTimeoutSeconds) {
			_VerticalAxis.transmission->SetVoltage(12 * 0.2);
		} else {
			_VerticalAxis.transmission->SetVoltage(0);
			_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 1);
			_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 1);
			std::cout << "Turret Zero Timed Out" << std::endl;
			break;
		}
	}
  _VerticalAxis.encoder->ZeroEncoder();
}


// Feedback for correct flywheel speeds
void Turret::ContFlywheelFeedback() {
  if (_FlyWheel.encoder->GetEncoderAngularVelocity() <= ControlMap::FlyWheelVelocity) {
		_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 1);
		_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 1);
	} else {
		_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kLeftRumble, 0);
		_contGroup.GetController(ControlMap::CoDriver).SetRumble(wml::controllers::RumbleType::kRightRumble, 0);
	}
}

// Tuner Control
void Turret::PIDTuner() {
  if (ControlMap::TuneTurretPID && ControlMap::TuneAnglePID) {
		std::cout << "Conflict Turret/Angle Tuning" << std::endl;
	}	else if (ControlMap::TuneTurretPID) {
		TuneTurretPID();
	} else if (ControlMap::TuneAnglePID) {
		TuneAnglePID();
	}
}

// Fly wheel Manual Control
void Turret::FlyWheelManualSpinup() {
	FlyWheelPower = _contGroup.Get(ControlMap::TurretFlyWheelSpinUp);
}

