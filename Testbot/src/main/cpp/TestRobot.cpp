#include "TestRobot.h"

#include "frc/AnalogInput.h"
#include <actuators/VoltageController.h>
#include "sensors/LimitSwitch.h"

#include <math.h>
#include <iostream>

using namespace frc;
using namespace wml;

double lastTimestamp;

using hand = frc::XboxController::JoystickHand;


void Robot::RobotInit() {
  // Get's last time stamp, used to calculate dt
  lastTimestamp = Timer::GetFPGATimestamp();
  BeltMotor = new VictorSpx(5);
  BeltMotor->SetInverted(false);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  double dt = Timer::GetFPGATimestamp() - lastTimestamp;

  auto inst = nt::NetworkTableInstance::GetDefault();
	auto visionTable = inst.GetTable("TestBot");
	auto table = visionTable->GetSubTable("Intake");

  table->PutBoolean("first Limit Switch", LimitSwitch0.Get());
  table->PutBoolean("second limit switch ", LimitSwitch1.Get());
  table->PutBoolean("top Limit switch", LimitSwitch2.Get());

  timer.Start();

  std::cout << "Timer Value " << timer.Get() << std::endl;
  if (LimitSwitch2.Get() > 0) {
    timer.Start();
    while (timer.Get() <= 0.7) {
      BeltMotor->Set(1);
    }
    BeltMotor->Set(0);
    timer.Stop();
    timer.Reset();
  }
  //to move a whole space its 1.1s to move from intake to space 1 its 0.7s
     
     // else if (LimitSwitch1.Get() > 0) {
      //   BeltMotor->Set(1);
      // } else if (LimitSwitch2.Get() > 0) {
      //   BeltMotor->Set(1);
      // } else {
      //   BeltMotor->Set(0);
      // } 
    

  
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
