#pragma once

#include <iostream>

// Opencv files
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Local Files
#include "Dashboard/Centeralnfo.h"
#include "Dashboard/Mag.h"
#include "Dashboard/Climber.h"
#include "Dashboard/Drive.h"
#include "Dashboard/Turret.h"

class GUI_Core : public Orientation {
  public:
    void GUI(int argc, char** argv);
  private:

    // functions
    cv::Mat CreateWindow(cv::Mat image, int argc, char** argv);
    void DisplayWindow(cv::Mat image);

    // Images
    cv::Mat window;

    // Instances
    CentralInfo centerInfo;
    Mag mag;
    Turret turret;
    Drive drive;
    Climber climber;

    Orientation orientation;

    double Auto;
    nt::NetworkTableEntry AutoSelector;
};