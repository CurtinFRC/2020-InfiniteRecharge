#include "Robot.h"

// Robot.cpp is our main entrypoint

// Note: If you try zero an encoder but the Motor controller is disconnected or doesn't exist
// The code will build, but it will not run on the robot. 

using namespace frc;
using namespace wml;

double lastTimestamp;

void Robot::RobotInit() {
  //robotMap.DriveSystem.LGearbox.transmission->SetInverted(true);

  std::cout << "Robot SetUp Complete" << std::endl;
}


void Robot::RobotPeriodic() {
  // In periodic mode. Continuous looped code
}

void Robot::DisabledInit() {
  InterruptAll(true);
}

void Robot::AutonomousInit() {
  //driveSystem->ZeroEncoder();
  //subSystem1->ZeroEncoder();
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  //driveSystem->ZeroEncoder();
  //subSystem1->ZeroEncoder();
}
void Robot::TeleopPeriodic() {
  //robotMap.DriveSystem.drivetrain.Set(1, -1);

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