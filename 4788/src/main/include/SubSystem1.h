#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"

class SubSystem1 {
  public:

  // ----------------Instances--------------------
  ControlMap *controlMap;

	// -------------Motor Definement----------------
  curtinfrc::TalonSrx *MotorSRX1, *MotorSRX2;

  // -------------Function Definement----------------
  SubSystem1(int SRX1_, int SRX2_);
  void zeroEncoder();
  void SubSystem1Control();
};