#include "Climber.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(actuators::DoubleSolenoid &ClimberActuator,
                 actuators::DoubleSolenoid &ShiftPTO, 
                 Gearbox &ClimberElevatorLeft, 
                 Gearbox &ClimberElevatorRight,
                 SmartControllerGroup &contGroup) : 

                 _ClimberActuator(ClimberActuator), 
                 _ShiftPTO(ShiftPTO), 
                 _ClimberElevatorLeft(ClimberElevatorLeft), 
                 _ClimberElevatorRight(ClimberElevatorRight),
                 _contGroup(contGroup) {}
void Climber::TeleopOnUpdate(double dt) {
  double liftSpeedleft;
  double liftSpeedright;
  if (_contGroup.Get(ControlMap::ClimberToggle, Controller::ONFALL)) {
    if (ToggleEnabled) {
      ToggleEnabled = false;
    } else if (!ToggleEnabled) {
      ToggleEnabled = true;
    }
  } 


  if (_contGroup.Get(ControlMap::Shift2PTO, Controller::ONFALL)) {
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

  if (ToggleEnabled) {

    liftSpeedleft = _contGroup.Get(ControlMap::ClimberControlLeft) > ControlMap::joyDeadzone ?  _contGroup.Get(ControlMap::ClimberControlLeft) : 0;
    liftSpeedright = _contGroup.Get(ControlMap::ClimberControlRight) > ControlMap::joyDeadzone ? _contGroup.Get(ControlMap::ClimberControlRight) : 0;
    liftSpeedright *= ControlMap::LiftMaxSpeed;
    liftSpeedleft *= ControlMap::LiftMaxSpeed;
    _ClimberElevatorLeft.transmission->SetVoltage(12 * liftSpeedleft);
    _ClimberElevatorRight.transmission->SetVoltage(12 * liftSpeedright);
  
  } else {
    _ClimberElevatorLeft.transmission->SetVoltage(0);
    _ClimberElevatorRight.transmission->SetVoltage(0);
  }



}

void Climber::AutoOnUpdate(double dt) {}

void Climber::TestOnUpdate(double dt) {
  double liftSpeed;

  _ShiftPTO.SetTarget(wml::actuators::kForward);
  _ClimberActuator.SetTarget(wml::actuators::kForward);
  if (_ClimberElevatorLeft.encoder->GetEncoderRotations() <= 6) {
    _ClimberElevatorLeft.transmission->SetVoltage(1);
  } else {
    _ClimberElevatorLeft.transmission->SetVoltage(0);
  }
  _ClimberActuator.SetTarget(wml::actuators::kReverse);
  _ShiftPTO.SetTarget(wml::actuators::kReverse);
}
  



