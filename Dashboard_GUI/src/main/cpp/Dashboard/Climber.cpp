#include "Dashboard/Climber.h"

void Climber::ClimberImage(cv::Mat *window, int posX, int posY) {

  cv::Point LeftLowerQuarter(posX, posY);

  cv::circle(*window, LeftLowerQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
}