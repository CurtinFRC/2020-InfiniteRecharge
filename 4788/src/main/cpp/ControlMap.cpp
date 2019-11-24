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
  CtrlMp.DriveSRXportL = 1;
  CtrlMp.DriveSPXportL = 2;
  // Drive Right
  CtrlMp.DriveSRXportR = 3;
  CtrlMp.DriveSPXportR = 4;

  // Subsystem1
  CtrlMp.Sub1SRXport1 = 5;
  CtrlMp.Sub1SRXport2 = 6;

  // Subsystem2
  CtrlMp.Sub2SPXport1 = 7;
}