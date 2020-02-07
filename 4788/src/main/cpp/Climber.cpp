#include "Climber.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(actuators::DoubleSolenoid &ClimberActuator, actuators::DoubleSolenoid &ShiftPTO, Gearbox &ClimberElevator, SmartControllerGroup &contGroup) : _ClimberActuator(ClimberActuator), _ShiftPTO(ShiftPTO), _ClimberElevator(ClimberElevator), _contGroup(contGroup) {}

void Climber::TeleopOnUpdate(double dt) {
  double liftSpeed;
  
  if (_contGroup.Get(ControlMap::PT2OShift, Controller::ONFALL)) {
    if (ToggleEnabled) {
      _ShiftPTO.SetTarget(wml::actuators::kForward);
      ToggleEnabled = false;
    } else if (!ToggleEnabled) {
      _ShiftPTO.SetTarget(wml::actuators::kReverse);
      ToggleEnabled = true;
    }
  }
  
  if (_contGroup.Get(ControlMap::ClimberUp, Controller::ONFALL)) {
    _ClimberActuator.SetTarget(wml::actuators::kForward);
    ToggleEnabled = false;
  } else if (!ToggleEnabled) {
    _ClimberActuator.SetTarget(wml::actuators::kReverse);
    ToggleEnabled = true;
  }

  // Climber Control
  liftSpeed = _contGroup.Get(ControlMap::ClimberControl) > ControlMap::joyDeadzone ?  _contGroup.Get(ControlMap::ClimberControl) : 0;
  liftSpeed *= ControlMap::LiftMaxSpeed;
  _ClimberElevator.transmission->SetVoltage(12 * liftSpeed);

}


void Climber::AutoOnUpdate(double dt) {}

void Climber::TestOnUpdate(double dt) {
  double liftSpeed;

  _ShiftPTO.SetTarget(wml::actuators::kForward);
  _ClimberActuator.SetTarget(wml::actuators::kForward);
  
  if (_ClimberElevator.encoder->GetEncoderRotations() <= 6) {
    _ClimberElevator.transmission->SetVoltage(1);
  } else {
    _ClimberElevator.transmission->SetVoltage(0);
  }
  
  _ClimberActuator.SetTarget(wml::actuators::kReverse);
  _ShiftPTO.SetTarget(wml::actuators::kReverse);
}
  



