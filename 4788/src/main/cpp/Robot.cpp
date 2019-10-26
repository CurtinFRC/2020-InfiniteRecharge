/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <frc/TimedRobot.h>
#include <ntcore.h>

#include "networktables/NetworkTableInstance.h"
#include "Robot.h"

class MyRobot : public frc::TimedRobot {

  nt::NetworkTableEntry VisionDistanceEntry;
  nt::NetworkTableEntry VisionXOffsetEntry;
  nt::NetworkTableEntry VisionYOffsetEntry;

  double variableXoffset;
  double variableYoffset;
 
  void RobotInit() override {
    auto inst = nt::NetworkTableInstance::GetDefault();
    auto visionTable = inst.GetTable("VisionTracking");
    auto table = visionTable->GetSubTable("VisionObjectTracking");
    VisionDistanceEntry = table->GetEntry("Hatch Distance");
    VisionXOffsetEntry = table->GetEntry("Vision X Offset");
    VisionYOffsetEntry = table->GetEntry("Vision Y Offset");
  }

  void AutonomousInit() override {
    std::cout << "DUN DUN DUUUUUUNNNNNN, cj built this code bitch. in other words. be prepared for it to utterly fuck you over" << std::endl;
  }
  
  void AutonomousPeriodic() override {
    VisionXOffsetEntry.GetDouble(variableXoffset);
    VisionYOffsetEntry.GetDouble(variableYoffset);
  }
  
  void TeleopInit() override {}
  
  void TeleopPeriodic() override {}
  
  void TestPeriodic() override {}

  void RobotPeriodic() override {}
};

int main() { return frc::StartRobot<MyRobot>(); }
