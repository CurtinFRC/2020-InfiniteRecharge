#pragma once

#include "VisTrack.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include <thread>

class curtin_frc_vision {
 public:
  void run();
 private:
  CJ::VisionTracking vision;
  nt::NetworkTableEntry TargetX;
  nt::NetworkTableEntry TargetY;
  nt::NetworkTableEntry ImageHeight;
  nt::NetworkTableEntry ImageWidth;
};