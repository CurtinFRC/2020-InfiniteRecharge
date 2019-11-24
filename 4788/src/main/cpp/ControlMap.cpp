#include "Robot.h"
#include "ControlMap.h"

using namespace frc;
using namespace curtinfrc;

// This is where you define which ports are used for your motors, pneumatics ect...
// -------------Defined Ports-------------------

// Controllers
const int ControlMap::Controller1Port = 0;
const int ControlMap::Controller2Port = 1;

// Drive Left
const int ControlMap::SRXportL = 1;
const int ControlMap::SPXportL = 2;
// Drive Right
const int ControlMap::SRXportR = 3;
const int ControlMap::SPXportR = 4;



// -------------Function Control----------------

ControlMap::ControlMap(int ControllerPort1_, int ControllerPort2_) {

  // Switch below around to use different controllers
  xbox1 = new XboxController(ControllerPort1_);
  xbox2 = new XboxController(ControllerPort2_);

  // joy1 = new Joystick(ControllerPort1_);
  // joy2 = new Joystick(ControllerPort2_);
}