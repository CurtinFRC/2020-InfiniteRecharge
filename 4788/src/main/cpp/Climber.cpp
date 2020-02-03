#include "Climber.h"
#include <iostream>

using namespace wml;
using namespace wml::controllers;

Climber::Climber(actuators::DoubleSolenoid &ClimberActuator, actuators::BinaryServo &ShiftPTO, Gearbox &ClimberElevator, SmartControllerGroup &contGroup) : _ClimberActuator(ClimberActuator), _ShiftPTO(ShiftPTO), _ClimberElevator(ClimberElevator), _contGroup(contGroup) {}

void Climber::TeleopOnUpdate(double dt) {
  // double liftSpeed;

  

  // liftSpeed = _contGroup.Get(ControlMap::ClimberControl);
  // _ClimberElevator.transmission->SetVoltage(12 * liftSpeed);
  

}
void Climber::AutoOnUpdate(double dt) {}

void Climber::TestOnUpdate(double dt) {
  // double liftSpeed;
  // int i = 0;
  // while( i >= 2){
  //   //number of times can be changed 
  //   timer.Start();
  //   _ClimberElevator.transmission->SetVoltage(1);
  //   while (timer < 45)  {
  //     _ClimberElevator.transmission->SetVoltage(0);
  //   }
  //   timer.Stop();
  //   timer.Reset();
  //   i = i + 1;
  }
  



