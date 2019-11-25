#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"

class SubSystem2 {
  public:

  // ----------------Instances--------------------
  ControlMap *controlMap;

	// -------------Motor Definement----------------
  curtinfrc::VictorSpx *MotorSPX1;

  // -------------Function Definement----------------
  SubSystem2(int SPX1_);
  void SubSystem2Control();
};