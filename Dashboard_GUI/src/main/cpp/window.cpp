#include "GUI.h"
#include "Dashboard/Orientation.h"

cv::Mat GUI_Core::CreateWindow() {
  std::cout << "Select Auto" << std::endl;
  std::cout << "1 = 8 Ball" << std::endl;
  std::cout << "2 = 6 Ball" << std::endl;
  std::cout << "3 = 3 Ball Left" << std::endl;
  std::cout << "4 = 3 Ball Mid" << std::endl;
  std::cout << "5 = 3 Ball Right" << std::endl;
  std::cout << "Auto: ";
  std::cin >> Auto; 
  std::cout << std::endl << std::endl;

  std::cout << "Specify Width and Height of window. If Zero (Default is 1440x1000)" << std::endl;

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

  cv::Mat image(Height, Width, CV_8UC3, cv::Scalar(0,0,0));

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