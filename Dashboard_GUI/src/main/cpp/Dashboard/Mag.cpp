#include "Dashboard/Mag.h"

void Mag::MagLoader(cv::Mat *window, int posX, int posY) {

  // Draw mag balls
  cv::Point LeftUpperQuarter(posX, posY);

  // Draw testpoints
  cv::circle(*window, LeftUpperQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
  // cv::circle(*window, RightUpperQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
  // cv::circle(*window, LeftLowerQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
  // cv::circle(*window, RightLowerQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);

  // cv::circle(*window, MidPoint, 10, cv::Scalar(0,0,255), CV_FILLED);
}