#include "Climber.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(actuators::DoubleSolenoid &ClimberActuator,
                 actuators::DoubleSolenoid &BeltActuator,
                 Gearbox &ClimberElevatorLeft, 
                 Gearbox &ClimberElevatorRight,
                 SmartControllerGroup &contGroup,
                 bool &TurretDisable) : 

                 _ClimberActuator(ClimberActuator), 
                 _BeltActuator(BeltActuator),
                 _ClimberElevatorLeft(ClimberElevatorLeft), 
                 _ClimberElevatorRight(ClimberElevatorRight),
                 _contGroup(contGroup),
                 _TurretDisable(TurretDisable) {}


void Climber::TeleopOnUpdate(double dt) {
  if (_contGroup.Get(ControlMap::ClimberToggle, Controller::ONRISE)) {

    // Put Intake down in up
    if (_BeltActuator.GetState() == wml::actuators::BinaryActuatorState::kReverse) {
      _BeltActuator.SetTarget(wml::actuators::BinaryActuatorState::kForward);
    }

    if (ToggleEnabled) {
      ToggleEnabled = false;
      _TurretDisable = false;
    } else if (!ToggleEnabled) {
      ToggleEnabled = true;
      _TurretDisable = true;
    }
  } 
 
  if (ToggleEnabled) {

    liftSpeedleft = _contGroup.Get(ControlMap::ClimberControlLeft) > ControlMap::joyDeadzone ?  _contGroup.Get(ControlMap::ClimberControlLeft) : 0;
    liftSpeedright = _contGroup.Get(ControlMap::ClimberControlRight) > ControlMap::joyDeadzone ? _contGroup.Get(ControlMap::ClimberControlRight) : 0;
    liftSpeedright *= ControlMap::LiftMaxSpeed;
    liftSpeedleft *= ControlMap::LiftMaxSpeed;
  
  }
}

void Climber::AutoOnUpdate(double dt) {}

void Climber::TestOnUpdate(double dt) {
  _ClimberActuator.SetTarget(wml::actuators::kForward);

  if (_ClimberElevatorLeft.encoder->GetEncoderRotations() <= 6) {
    _ClimberElevatorLeft.transmission->SetVoltage(0.5);
    _ClimberElevatorRight.transmission->SetVoltage(0.5);
  } else {
    _ClimberElevatorLeft.transmission->SetVoltage(0);
    _ClimberElevatorRight.transmission->SetVoltage(0);
  }
  _ClimberActuator.SetTarget(wml::actuators::kReverse);
}
