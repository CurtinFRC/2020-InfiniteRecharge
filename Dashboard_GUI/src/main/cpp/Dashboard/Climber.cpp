#include "Dashboard/Climber.h"

void Climber::ClimberImage(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int posY) {

  cv::Point LeftLowerQuarter(posX, posY);

  cv::circle(*window, LeftLowerQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
}