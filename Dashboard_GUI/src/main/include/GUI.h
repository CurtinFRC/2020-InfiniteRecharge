#pragma once

#include <iostream>

// Opencv files
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Local Files
#include "Dashboard/Image.h"
#include "Dashboard/Mag.h"
#include "Dashboard/Climber.h"
#include "Dashboard/Drive.h"
#include "Dashboard/Turret.h"

class GUI_Core : public Orientation {
  public:
    void GUI();
  private:

    // functions
    cv::Mat CreateWindow();
    void DisplayWindow(cv::Mat image);

    // Images
    cv::Mat window;

    // Instances
    Mag mag;
    Turret turret;
    Drive drive;
    Climber climber;

    Orientation orientation;

    double Auto;
    nt::NetworkTableEntry AutoSelector;
};