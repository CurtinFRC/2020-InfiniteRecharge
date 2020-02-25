// #include "GUI.h"

// // Circle With smilely face. :)
// cv::Mat DrawImage(cv::Mat *Window) {


//   // draw the main circle
//   cv::Point centerCircle1(250, 250);
//   int radiusCircle = 100;
//   cv::Scalar colourCircle1(0, 255, 255);
//   int thicknessCircle1 = 2;
//   // cv::circle(*Window, centerCircle1, radiusCircle, colourCircle1, thicknessCircle1);
//   cv::circle(*Window, centerCircle1, radiusCircle, colourCircle1, CV_FILLED);

  
//   // draw eyes
//   cv::Point leftEye(200, 210);
//   cv::Point rightEye(300, 210);
//   int eyeRadius = 30;
//   cv::Scalar colourEye(0, 0, 0);
//   cv::circle(*Window, leftEye, eyeRadius, colourEye, CV_FILLED);
//   cv::circle(*Window, rightEye, eyeRadius, colourEye, CV_FILLED);

//   // static mouth
//   cv::Point mouthStart(200, 300), mouthEnd(300, 300);
//   cv::line(*Window, mouthStart, mouthEnd, cv::Scalar(0, 0, 0), 10);

//   return *Window;
// }