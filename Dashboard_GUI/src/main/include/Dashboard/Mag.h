#pragma once

#include "Dashboard/Orientation.h"

class Mag {
  public:
    void MagLoader(cv::Mat *Window, nt::NetworkTableInstance *inst, int posX, int posY);
  private:
    // Network table
    nt::NetworkTableEntry MagPower;
    nt::NetworkTableEntry MagEncoder;
    nt::NetworkTableEntry StartSensor;
    nt::NetworkTableEntry SecondSensor;
    nt::NetworkTableEntry LastSensor;
    nt::NetworkTableEntry Override;

    frc::Timer timer;
    frc::Timer testTimer;
};