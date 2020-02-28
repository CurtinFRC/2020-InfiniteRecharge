#include "GUI.h"
#include "Dashboard/Orientation.h"


cv::Mat GUI_Core::CreateWindow(cv::Mat image, int argc, char** argv) {

  std::cout << "Select Auto" << std::endl;
  std::cout << "1 = 8 Ball" << std::endl;
  std::cout << "2 = 6 Ball" << std::endl;
  std::cout << "3 = 3 Ball Left" << std::endl;
  std::cout << "4 = 3 Ball Mid" << std::endl;
  std::cout << "5 = 3 Ball Right" << std::endl;
  std::cout << "Auto: ";
  std::cin >> Auto;
  std::cout << std::endl << std::endl;

  Width = Default_Width;
  Height = Default_Height;

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


  #ifdef __DESKTOP__
  cv::String imageName( "C:\\Users\\Public\\DASH_GUI.png" ); // by default
  #else 
  std::cout << "This program is not compatable with other operating systems yet. Please use windows" << std::endl;
  exit(EXIT_FAILURE);
  #endif
  
  if (argc > 1) {
    imageName = argv[1];
  }
  image = cv::imread( cv::samples::findFile(imageName), cv::IMREAD_COLOR ); // Read the file
  if (image.empty()) {
    std::cout <<  "Could not open or find the image" << std::endl;
  }

  if (!image.data) {
    std::cout << "Could Not Create Window" << std::endl;
    exit(EXIT_FAILURE);
  }

  return image;
}

cv::Mat GUI_Core::RefreshWindow(cv::Mat image, int argc, char** argv) {
  cv::String imageName( "C:\\Users\\Public\\DASH_GUI.png" ); // by default
  if (argc > 1) {
    imageName = argv[1];
  }
  image = cv::imread( cv::samples::findFile(imageName), cv::IMREAD_COLOR ); // Read the file
  if (image.empty()) {
    std::cout <<  "Could not open or find the image" << std::endl;
  }

  if (!image.data) {
    std::cout << "Error Getting Window Data" << std::endl;
    exit(EXIT_FAILURE);
  }

  return image;
}


void GUI_Core::DisplayWindow(cv::Mat image) {
  cv::namedWindow("Curtin GUI", CV_WINDOW_AUTOSIZE);
  cv::imshow("Curtin GUI", image);
  cv::waitKey(30);
}