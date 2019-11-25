#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"

class PneumaticSystem1 {
  public:

  // ----------------Instances--------------------
  ControlMap *controlMap;

	// -------------Pneumatic Definement----------------
  curtinfrc::actuators::DoubleSolenoid *Pneumatic1;
  curtinfrc::actuators::DoubleSolenoid *Pneumatic2;

  // -------------Function Definement----------------
  
};