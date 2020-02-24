#include "GUI.h"
#include "Dashboard/Orientation.h"

cv::Mat GUI_Core::CreateWindow() {

  std::cout << "Specify Width and Height of window. If Zero (Default is 500x500)" << std::endl;

  std::cout << "Width: ";
  std::cin >> Width;
  std::cout << std::endl;
  if (Width <= 0) {
    Width = Default_Width;
    Height = Default_Height;
  } else {
    std::cout << "Height: ";
    std::cin >> Height;
    std::cout << std::endl;
    if (Height <= 0) {
      Height = Default_Height;
    }
  }

  WidthHalf = (Width/2);
  HeightHalf = (Height/2);

  WidthQuarter = (Width/4);
  HeightQuarter = (Height/4);

  WidthTwoThird = (WidthHalf+WidthQuarter);
  HeightTwoThird = (HeightHalf+HeightQuarter);

  LeftUpperQuarterX = WidthQuarter;
  LeftUpperQuarterY = HeightQuarter;

  RightUpperQuarterX = WidthTwoThird;
  RightUpperQuarterY = HeightQuarter;

  LeftLowerQuarterX = WidthQuarter;
  LeftLowerQuarterY = HeightTwoThird;

  RightLowerQuarterX = WidthTwoThird;
  RightLowerQuarterY = HeightTwoThird;
  // Quarters Points
  // LeftUpperQuarter(WidthQuarter, HeightQuarter);
  // RightUpperQuarter(WidthTwoThird, HeightQuarter);
  // LeftLowerQuarter(WidthQuarter, HeightTwoThird);
  // RightLowerQuarter(WidthTwoThird, HeightTwoThird);

  // MidPoint(WidthHalf, HeightHalf);

  // // Quarters Points
  // LeftUpperQuarter = new cv::Point(WidthQuarter, HeightQuarter);
  // RightUpperQuarter = new cv::Point(WidthTwoThird, HeightQuarter);
  // LeftLowerQuarter = new cv::Point(WidthQuarter, HeightTwoThird);
  // RightLowerQuarter = new cv::Point(WidthTwoThird, HeightTwoThird);

  // MidPoint = new cv::Point(WidthHalf, HeightHalf);


  cv::Mat image(Width, Height, CV_8UC3, cv::Scalar(0,0,0));

  if (!image.data) {
    std::cout << "Could Not Create Window" << std::endl;
    exit(EXIT_FAILURE);
  }

  return image;
}

void GUI_Core::DisplayWindow(cv::Mat image) {
  cv::imshow("GUI", image);
  cv::waitKey(30);
}