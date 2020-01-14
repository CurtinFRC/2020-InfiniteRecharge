#include "Turret.h"

std::string Turret::GetStateString() {
	switch (GetState()) {
	 case TurretState::kManual:
	 	return "kManual";
		break;

   case TurretState::kSetpoint:
    return "kSetPoint";
		break;

   case TurretState::kZeroing:
    return "kZeroing";
	 	break;
	}

	return "<State Error>";
};

void Turret::SetManual(double power) {};
void Turret::SetSetpoint(double setpoint) {};
void Turret::SetZeroing() {};


void Turret::OnStatePeriodic(TurretState state, double dt) {
  switch (state) {
   case TurretState::kManual:
    _config.horizontalAxis.transmission->SetVoltage(12 * GetSetpoint().first);
		_config.verticalAxis.transmission->SetVoltage(12 * GetSetpoint().second);
    break;

   case TurretState::kSetpoint:
    _config.horizontalAxis.transmission->SetVoltage(0 * GetSetpoint().first);		// TEMP - requires 'set to encoder'
		_config.verticalAxis.transmission->SetVoltage(0 * GetSetpoint().second);		// TEMP - requires 'set to encoder'
    break;

   case TurretState::kZeroing:
    if (_config.limitSensorHorizontal != nullptr) {
			if (!_config.limitSensorHorizontal->Get()) {
				// Turn towards the limit switch -- TEMP
				_config.horizontalAxis.transmission->SetVoltage(-0.1);
			} else _config.horizontalAxis.transmission->SetVoltage(0);
		} else _config.horizontalAxis.transmission->SetVoltage(0);

		if (_config.limitSensorVertical != nullptr) {
			if (!_config.limitSensorVertical->Get()) {
				// Turn towards the limit switch  --  TEMP
				_config.verticalAxis.transmission->SetVoltage(-0.1);
			} else _config.verticalAxis.transmission->SetVoltage(0);
		} else _config.verticalAxis.transmission->SetVoltage(0);
    break;
  }
};