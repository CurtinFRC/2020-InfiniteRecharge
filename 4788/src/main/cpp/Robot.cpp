#include "Robot.h"

// Robot.cpp is our main entrypoint

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {
  robotMap.driveSystem.LGearbox.transmission->SetInverted(true);
  robotMap.driveSystem.RGearbox.transmission->SetInverted(false);
  

  drivetrain->StartLoop(100);

  std::cout << "Robot SetUp Complete" << std::endl;
}


void Robot::RobotPeriodic() {

}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {
  //driveSystem->ZeroEncoder();
  //subSystem1->ZeroEncoder();
}
void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
  //driveSystem->ZeroEncoder();
  //subSystem1->ZeroEncoder();
}
void Robot::TeleopPeriodic() {
  robotMap.driveSystem.drivetrain.Set(1, -1);
  

  // subSystem1->SubSystem1Control();
  // subSystem2->SubSystem2Control();

  // #if __CONTROLMAP__USING_JOYSTICK__

  //   if (_robotmap->joy1.GetButton(ControlMap::SubSystem1Up)) {
  //     _robotmap->SubSystem1SRX1.Set(0.3);
  //     _robotmap->SubSystem1SRX2.Set(0.3);
  //   } else if (_robotmap->joy1.GetButton(controlMap->SubSystem1Down)) {
  //     _robotmap->SubSystem1SRX1.Set(-0.3);
  //     _robotmap->SubSystem1SRX2.Set(-0.3);
  //   } else {
  //     _robotmap->SubSystem1SRX1.Set(0);
  //     _robotmap->SubSystem1SRX2.Set(0);
  //   }
  // #else
  //   if (_robotmap->xbox1.GetButton(ControlMap::SubSystem1Up)) {
  //     _robotmap->SubSystem1SRX1.Set(0.3);
  //     _robotmap->SubSystem1SRX2.Set(0.3);
  //   } else if (_robotmap->xbox1.GetButton(ControlMap::SubSystem1Down)) {
  //     _robotmap->SubSystem1SRX1.Set(-0.3);
  //     _robotmap->SubSystem1SRX2.Set(-0.3);
  //   } else {
  //     _robotmap->SubSystem1SRX1.Set(0);
  //     _robotmap->SubSystem1SRX2.Set(0);
  //   }
  
  // #endif
} 

void Robot::TestInit() {
  //driveSystem->ZeroEncoder();
  //subSystem1->ZeroEncoder();
}
void Robot::TestPeriodic() {}