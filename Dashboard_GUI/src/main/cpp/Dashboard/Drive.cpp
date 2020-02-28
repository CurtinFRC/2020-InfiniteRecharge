#include "Dashboard/Drive.h"

int testPos = 900;

void Drive::DriveImage(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int posY) {
  cv::Point RightLowerQuarter(posX, posY);


  cv::Point LDriveStart(1100, 480), LDriveEnd(1100, 715);
  cv::Point RDriveStart(1307, 480), RDriveEnd(1307, 715);

  cv::Point LDPwr(925, 650);
  cv::Point LDEC(925, 700);

  cv::Point RDPwr(1330, 650);
  cv::Point RDEC(1330, 700);

  auto DriveTable = inst->GetTable("DriveTable");

  LPower = DriveTable->GetEntry("LPower");
  RPower = DriveTable->GetEntry("RPower");
  LEC = DriveTable->GetEntry("LEC");
  REC = DriveTable->GetEntry("REC");

  // cv::circle(*window, RightLowerQuarter, 10, cv::Scalar(0,0,255), CV_FILLED);

  double NTPowerL = (LPower.GetDouble(0)*255);
  double NTPowerR = (RPower.GetDouble(0)*255);

  cv::line(*window, LDriveStart, LDriveEnd, cv::Scalar(0,0,NTPowerL), 5);
  cv::line(*window, RDriveStart, RDriveEnd, cv::Scalar(NTPowerR,0,0), 5);

  std::string LPowerS = std::to_string(LPower.GetDouble(0));
  std::string RPowerS = std::to_string(RPower.GetDouble(0));
  std::string LECS = std::to_string(LEC.GetDouble(0));


  // Put Values
  cv::putText(*window, "PW: " + LPowerS, LDPwr, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));
  cv::putText(*window, "EC: " + LECS, LDEC, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));

  cv::putText(*window, "PW: " + LPowerS, RDPwr, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));
  cv::putText(*window, "EC: " + LECS, RDEC, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));
}