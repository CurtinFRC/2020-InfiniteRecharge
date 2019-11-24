#include "ControlMap.h"

using namespace frc;
using namespace curtinfrc;

// This is where you define which ports are used for your motors, pneumatics ect...

// -------------Defined Ports-------------------
void DefinePorts() {
  ControlMap CtrlMp;
  // Controllers
  CtrlMp.XboxController1Port = 0;
  CtrlMp.XboxController2Port = 1;

  // Drive Left
  CtrlMp.SRXportL = 1;
  CtrlMp.SPXportL = 2;
  // Drive Right
  CtrlMp.SRXportR = 3;
  CtrlMp.SPXportR = 4;
}