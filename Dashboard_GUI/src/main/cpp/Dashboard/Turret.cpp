#include "Dashboard/Turret.h"

void Turret::TurretImage(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int posY) {

  cv::Point RightUpperQuarter(posX, posY);

  cv::circle(*window, RightUpperQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);
}