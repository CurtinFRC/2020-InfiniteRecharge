#include "SubSystem2.h"
#include "ControlMap.h"
#include "Robot.h"

// This Subsystem will be an intake system with 1 motor.
// intakes don't need encoders because it's constant movement 
// with no automation. more or less power, no power or negative power.
// Because of this we can use Victors instead

SubSystem2::SubSystem2(int SPX1_) {

  // Initialise Motors
  MotorSPX1 = new curtinfrc::VictorSpx(SPX1_);
}

void SubSystem2::SubSystem2Control() {
  if (controlMap->SubSystem2Intake) {
    MotorSPX1->Set(1);
  } else if (controlMap->SubSystem2Outtake) {
    MotorSPX1->Set(-1);
  } else {
    MotorSPX1->Set(0);
  }
}