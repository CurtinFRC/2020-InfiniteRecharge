#include "SubSystem2.h"
#include "ControlMap.h"

using namespace wml;
using namespace wml::controllers;
using namespace wml::actuators;

std::string SubSystem2::GetStateString() {
  switch (GetState()) {
   case SubSystem2State::kIdle:
    return "kIdle";
    
   case SubSystem2State::kIntaking:
    return "kIntaking";
    
   case SubSystem2State::kOuttaking:
    return "kOuttaking";
  }

  return "<state error>";
}

void SubSystem2::SetIdle() {
  SetState(SubSystem2State::kIdle);
}

void SubSystem2::SetIntaking() {
  SetState(SubSystem2State::kIntaking);
}

void SubSystem2::SetOuttaking() {
  SetState(SubSystem2State::kOuttaking);
}

void SubSystem2::OnStatePeriodic(SubSystem2State state, double dt) {
  double speed = 0;
  
  switch (state) {
   case SubSystem2State::kOuttaking:
    speed = -ControlMap::SubSystem2Speed;
    break;

   case SubSystem2State::kIntaking:
    speed = ControlMap::SubSystem2Speed;
    break;

   case SubSystem2State::kIdle:
    speed = ControlMap::SubSystem2IdleSpeed;
    break;
  }

  _config.actuator.SetTarget(state == SubSystem2State::kOuttaking ? kForward : kReverse);
  _config.gearbox.transmission->SetVoltage(speed * 12.0);
}


SubSystem2ManualStrategy::SubSystem2ManualStrategy(std::string name, SubSystem2 &subsys2, SmartController &cont1, SmartController &cont2) : Strategy(name), _subsys2(subsys2), _cont1(cont1), _cont2(cont2) {
  SetCanBeInterrupted(true);
  SetCanBeReused(true);
} 

void SubSystem2ManualStrategy::OnUpdate(double dt) {
  if (_cont1.Get(ControlMap::SubSystem2Intake)) {
    _subsys2.SetIntaking();
  } else if (_cont1.Get(ControlMap::SubSystem2Outtake)) {
    _subsys2.SetOuttaking();
  } else {
    _subsys2.SetIdle();
  }
}

