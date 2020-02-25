#include "Dashboard/Mag.h"

void Mag::MagLoader(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int posY) {

  // Draw mag balls
  cv::Point LeftUpperQuarter(posX, posY);

  // Draw testpoints
  cv::circle(*window, LeftUpperQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
}