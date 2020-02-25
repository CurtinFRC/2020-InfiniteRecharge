#include "Dashboard/Mag.h"

void Mag::MagLoader(cv::Mat *window, nt::NetworkTableInstance *inst, int posX, int posY) {

  // mag ball points
  cv::Point StartBall(500, 200);
  cv::Point SecondBall(417, 200);
  cv::Point ThirdBall(332, 200);
  cv::Point FinalBall(263, 161);

  // Override Points
  cv::Point OverridePoint(570, 115);
  cv::Rect OverrideRect(545, 99, 170, 22);
  
  // Loading Points
  cv::Point LoadingPoint(575, 169);
  cv::Rect LoadingRect(545, 152, 170, 22);

  // GT Fire
  cv::Point GTFPoint(577, 192);
  cv::Rect GTFRect(545, 175, 170, 22);

  // Mag Values
  cv::Point PowerPoint(170, 300);
  cv::Point EncoderPoint(400, 300);


  timer.Start();

  // Mag connection
  auto MagTable = inst->GetTable("MagTable");

  // Entry's
  MagPower = MagTable->GetEntry("MagPower");
  MagEncoder = MagTable->GetEntry("MagEncoder");
  StartSensor = MagTable->GetEntry("StartSensor");
  SecondSensor = MagTable->GetEntry("SecondSensor");
  LastSensor = MagTable->GetEntry("LastSensor");
  Override = MagTable->GetEntry("Override");

  int CaseNumber = 3; // Default = Loading
  bool Test = false;

  // Control Statement
  if (Test) {
    testTimer.Start();
    if (testTimer.Get() < 1) {
      CaseNumber = 1;
    } else if (testTimer.Get() < 2 ) {
      CaseNumber = 3;
    } else if (testTimer.Get() < 3) {
      CaseNumber = 2;
    } else {
      testTimer.Reset();
    }
  } else {
    if (Override.GetBoolean(false)) {
      CaseNumber = 1;
    } else {
      if (LastSensor.GetDouble(0) >= 1100) {
        CaseNumber = 2;
      } else if ((StartSensor.GetDouble(0) >= 700) || (SecondSensor.GetDouble(0) >= 2000)) {
        CaseNumber = 3;
      }
    }
  }



  switch (CaseNumber) {

    // Override
    case 1:
      // Loading Clear
      cv::putText(*window, "LOADING", LoadingPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
      cv::rectangle(*window, LoadingRect, cv::Scalar(0,0,0));

      // GT Fire Clear
      cv::putText(*window, "GT FIRE", GTFPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
      cv::rectangle(*window, GTFRect, cv::Scalar(0,0,0));

      cv::putText(*window, "OVERRIDE", OverridePoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,255));
      cv::rectangle(*window, OverrideRect, cv::Scalar(0,0,255));
      cv::circle(*window, StartBall, 35, cv::Scalar(0,0,255), CV_FILLED);
      cv::circle(*window, SecondBall, 35, cv::Scalar(0,0,255), CV_FILLED);
      cv::circle(*window, ThirdBall, 35, cv::Scalar(0,0,255), CV_FILLED);
      cv::circle(*window, FinalBall, 35, cv::Scalar(0,0,255), CV_FILLED);
    break;

    // GT Fire
    case 2:
      // Override Clear
      cv::putText(*window, "OVERRIDE", OverridePoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
      cv::rectangle(*window, OverrideRect, cv::Scalar(0,0,0));

      // Loading Clear
      cv::putText(*window, "LOADING", LoadingPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
      cv::rectangle(*window, LoadingRect, cv::Scalar(0,0,0));

      cv::putText(*window, "GT FIRE", GTFPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));
      cv::rectangle(*window, GTFRect, cv::Scalar(0,255,0));
      cv::circle(*window, StartBall, 35, cv::Scalar(0,255,0), CV_FILLED);
      cv::circle(*window, SecondBall, 35, cv::Scalar(0,255,0), CV_FILLED);
      cv::circle(*window, ThirdBall, 35, cv::Scalar(0,255,0), CV_FILLED);
      cv::circle(*window, FinalBall, 35, cv::Scalar(0,255,0), CV_FILLED);
    break;

    // Loading
    case 3:
      // Override Clear
      cv::putText(*window, "OVERRIDE", OverridePoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
      cv::rectangle(*window, OverrideRect, cv::Scalar(0,0,0));

      // GT Fire Clear
      cv::putText(*window, "GT FIRE", GTFPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,0,0));
      cv::rectangle(*window, GTFRect, cv::Scalar(0,0,0));

      cv::putText(*window, "LOADING", LoadingPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,255));
      cv::rectangle(*window, LoadingRect, cv::Scalar(0,255,255));
      if (timer.Get() < 0.2) {
        cv::circle(*window, StartBall, 35, cv::Scalar(0,255,255), CV_FILLED);
      } else if (timer.Get() < 0.4) {
        cv::circle(*window, SecondBall, 35, cv::Scalar(0,255,255), CV_FILLED);
      } else if (timer.Get() < 0.6) {
        cv::circle(*window, ThirdBall, 35, cv::Scalar(0,255,255), CV_FILLED);
      } else if (timer.Get() < 0.8) {
        cv::circle(*window, FinalBall, 35, cv::Scalar(0,255,255), CV_FILLED);
      } else {
        cv::circle(*window, StartBall, 35, cv::Scalar(0,0,0), CV_FILLED);
        cv::circle(*window, SecondBall, 35, cv::Scalar(0,0,0), CV_FILLED);
        cv::circle(*window, ThirdBall, 35, cv::Scalar(0,0,0), CV_FILLED);
        cv::circle(*window, FinalBall, 35, cv::Scalar(0,0,0), CV_FILLED);
        timer.Reset();
      }
    break;
  }
  std::string MagPowerS = std::to_string(MagPower.GetDouble(0));
  std::string MagEncoderS = std::to_string(MagEncoder.GetDouble(0));

  // Put Values
  cv::putText(*window, "PW: " + MagPowerS, PowerPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));
  cv::putText(*window, "EC: " + MagEncoderS, EncoderPoint, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0,255,0));
}