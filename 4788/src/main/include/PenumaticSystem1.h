#pragma once

#include "Robot.h"

class PneumaticSystem1 : public frc::TimedRobot, protected curtinfrc::StrategyController, protected curtinfrc::NTProvider {
  public:

	// -------------Pneumatic Definement----------------
  curtinfrc::actuators::DoubleSolenoid *Pneumatic1;
  curtinfrc::actuators::DoubleSolenoid *Pneumatic2;

  // -------------Function Definement----------------
  
};