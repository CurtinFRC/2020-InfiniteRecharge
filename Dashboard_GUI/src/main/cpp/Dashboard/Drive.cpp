#include "Dashboard/Drive.h"

void Drive::DriveImage(cv::Mat *window, int posX, int posY) {

  cv::Point RightLowerQuarter(posX, posY);

  cv::circle(*window, RightLowerQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
}