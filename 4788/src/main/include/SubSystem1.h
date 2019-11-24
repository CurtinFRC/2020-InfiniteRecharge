#pragma once

#include "Robot.h"

// This SubSystem will just be an assumed pendulum movement with 2 motors
// similar to 5663's KillSwitch Bucket Intake

class SubSystem {
  public:

	// -------------Motor Definement----------------
  curtinfrc::TalonSrx *MotorSRX1, *MotorSRX2;

  // -------------Function Definement----------------
  SubSystem(int SRX1_, int SRX2_);
};