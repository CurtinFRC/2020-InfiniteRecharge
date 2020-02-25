#pragma once

#include "Dashboard/Orientation.h"

class CentralInfo {
  public:
    void CentralInfoImage(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int PosY);
  private:
    //Network Table and stuff
    nt::NetworkTableEntry AutoSelector;
    nt::NetworkTableEntry RobotActive;
    frc::Timer timer;
};