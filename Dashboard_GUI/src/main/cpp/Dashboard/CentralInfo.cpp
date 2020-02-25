#include "Dashboard/Centeralnfo.h"

void CentralInfo::CentralInfoImage(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int posY) {
  cv::Point ConnectionPoint(670, 300);
  cv::Point TextOffset(0, 0);
  cv::Point Center(800, 450);

  // Tables
  auto activeTable = inst->GetTable("Activity");
  nt::NetworkTableEntry RobotActive;

  // Entry's
  RobotActive = activeTable->GetEntry("ActiveRobot");

  timer.Start();

  // IF robot is disconneted
  if (RobotActive.GetBoolean(false) == false) {
    if ((int)(timer.Get()) % 2) {
      cv::putText(*window, "ROBOT DISCONNECTED", ConnectionPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,255));
    } else {
      cv::putText(*window, "ROBOT DISCONNECTED", ConnectionPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
    }
  }
}