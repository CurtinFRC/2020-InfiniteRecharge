#pragma once

#include "GeneralLibs/GeneralLibs.h"

class SubSystem1 {
  public:

	// -------------Motor Definement----------------
  curtinfrc::TalonSrx *MotorSRX1, *MotorSRX2;

  // -------------Function Definement----------------
  SubSystem1(int SRX1_, int SRX2_);
  void zeroEncoder();
};