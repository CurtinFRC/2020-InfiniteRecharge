#pragma once

// Network Tables
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

// Opencv files
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Structure
/**
 * Upper left quarter = mag
 * Upper right quater = Turret
 * Lower right quater = Drive
 * Lower left quater = climber
 * middle = regular values
*/ 

class Orientation {
  public:
    // Window Size
    int Width, Height; // deafult is 500x500
    int Default_Width = 500, Default_Height = 500;

    int WidthHalf;
    int HeightHalf;

    int WidthQuarter;
    int HeightQuarter;

    int WidthTwoThird;
    int HeightTwoThird;

    // Quarters Points
    int LeftUpperQuarterX, LeftUpperQuarterY;
    int RightUpperQuarterX, RightUpperQuarterY;
    int LeftLowerQuarterX, LeftLowerQuarterY;
    int RightLowerQuarterX, RightLowerQuarterY;
};