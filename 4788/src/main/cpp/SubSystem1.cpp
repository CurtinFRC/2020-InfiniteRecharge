#include "SubSystem1.h"
#include "ControlMap.h"
#include "Robot.h"

// This SubSystem will just be an assumed pendulum movement with 2 motors
// similar to 5663's KillSwitch Bucket Intake

SubSystem1::SubSystem1(RobotMap &robotMap) {

  // Initialise Motors
  
  robotMap.SubSystem1SRX1.SetInverted(true);

  // Zero Encoders (Only SRX's Have encoders)
  SubSystem1::zeroEncoder();
}

void SubSystem1::zeroEncoder() {
  _robotmap->SubSystem1SRX1.ZeroEncoder();
  _robotmap->SubSystem1SRX2.ZeroEncoder();
}

void SubSystem1::SubSystem1Control() {

  #if __CONTROLMAP__USING_JOYSTICK__

    if (_robotmap->joy1.GetButton(ControlMap::SubSystem1Up)) {
      _robotmap->SubSystem1SRX1.Set(0.3);
      _robotmap->SubSystem1SRX2.Set(0.3);
    } else if (_robotmap->joy1.GetButton(controlMap->SubSystem1Down)) {
      _robotmap->SubSystem1SRX1.Set(-0.3);
      _robotmap->SubSystem1SRX2.Set(-0.3);
    } else {
      _robotmap->SubSystem1SRX1.Set(0);
      _robotmap->SubSystem1SRX2.Set(0);
    }
  #else
    if (_robotmap->xbox1.GetButton(ControlMap::SubSystem1Up)) {
      _robotmap->SubSystem1SRX1.Set(0.3);
      _robotmap->SubSystem1SRX2.Set(0.3);
    } else if (_robotmap->xbox1.GetButton(ControlMap::SubSystem1Down)) {
      _robotmap->SubSystem1SRX1.Set(-0.3);
      _robotmap->SubSystem1SRX2.Set(-0.3);
    } else {
      _robotmap->SubSystem1SRX1.Set(0);
      _robotmap->SubSystem1SRX2.Set(0);
    }
  
  #endif
}