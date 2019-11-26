#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"

class PneumaticSystem2 {
  public:

  // ----------------Instances--------------------
  ControlMap *controlMap;

	// -------------Pneumatic Definement----------------
  wml::actuators::DoubleSolenoid *Pneumatic1;
  wml::actuators::DoubleSolenoid *Pneumatic2;

  // -------------Function Definement----------------
  
};