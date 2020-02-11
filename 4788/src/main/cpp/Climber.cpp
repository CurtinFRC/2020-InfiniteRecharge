#include "Climber.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(actuators::DoubleSolenoid &ClimberActuator, 
                 Gearbox &ClimberElevator, 
                 SmartControllerGroup &contGroup) : 

                 _ClimberActuator(ClimberActuator), 
                 _ClimberElevator(ClimberElevator), 
                 _contGroup(contGroup) {}


void Climber::TeleopOnUpdate(double dt) {
  double liftSpeed = 0;
  
  
  if (_contGroup.Get(ControlMap::ClimberUp, Controller::ONRISE)) {

    if (ToggleEnabled) {
      _ClimberActuator.SetTarget(wml::actuators::kForward);
      ToggleEnabled = false;
    } else if (!ToggleEnabled) {
      _ClimberActuator.SetTarget(wml::actuators::kReverse);
      ToggleEnabled = true;
    }
  } 

  liftSpeed = _contGroup.Get(ControlMap::ClimberControl) > ControlMap::joyDeadzone ?  _contGroup.Get(ControlMap::ClimberControl) : 0;
  liftSpeed *= ControlMap::LiftMaxSpeed;
  _ClimberElevator.transmission->SetVoltage(12 * liftSpeed);
}

void Climber::AutoOnUpdate(double dt) {}

void Climber::TestOnUpdate(double dt) {
  liftSpeed = 0.25;
  switch (testType) {
    case 1:
      _ClimberActuator.SetTarget(wml::actuators::kForward);
      if (_ClimberElevator.encoder->GetEncoderRotations() <= 6) {
        _ClimberElevator.transmission->SetVoltage(12 * liftSpeed);
      } else {
        testType++;
      }
    break;

    case 2:
      if (_ClimberElevator.encoder->GetEncoderRotations() >= 6) {
        _ClimberElevator.transmission->SetVoltage(12 * -liftSpeed);
      } else {
        testType++;
      }
    break;

    case 3:
      _ClimberActuator.SetTarget(wml::actuators::kReverse);
    break;
  }

  _ClimberActuator.Update(dt);
}
  



