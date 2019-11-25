#include "SubSystem1.h"
#include "ControlMap.h"
#include "Robot.h"

// This SubSystem will just be an assumed pendulum movement with 2 motors
// similar to 5663's KillSwitch Bucket Intake

SubSystem1::SubSystem1(int SRX1_, int SRX2_) {

  // Initialise Motors
  MotorSRX1 = new curtinfrc::TalonSrx(SRX1_);
  MotorSRX2 = new curtinfrc::TalonSrx(SRX2_);

  // Zero Encoders (Only SRX's Have encoders)
  SubSystem1::zeroEncoder();
}

void SubSystem1::zeroEncoder() {
  MotorSRX1->ZeroEncoder();
  MotorSRX2->ZeroEncoder();
}