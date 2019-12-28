#pragma once

#include "VisTrack.h"
#include <thread>

class curtin_frc_vision {
 public:
  void run();
 private:
  CJ::VisionTracking vision;
};