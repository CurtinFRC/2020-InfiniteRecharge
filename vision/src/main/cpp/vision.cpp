#include "vision.h"
#include <thread>

//cv::RNG rng(12345);
//cv::Rect bounding_rect;
int thresh = 100;
float height_offset;
float width_offset;
int ResWidth = 640, ResHeight = 480;
float width_goal;
float height_goal;

cv::Mat Image; // Origin Image
cv::Mat TrackingImage; // Imaged After it has been procesed

void curtin_frc_vision::run() {
	Image = vision.SetupVision(1, 60, ResHeight, ResWidth, 30, "Testing Cam", true);

	while (true) {
		if (vision.Camera.cam.sink.GrabFrame(Image) !=0) {
			TrackingImage = vision.RetroTrack(Image, 2, 2);

			cv::imshow("Origin Image", Image);
			cv::imshow("Green Track Image", TrackingImage);
		} else{
			std::cout << "Error Getting Image" << std::endl;
		}
		cv::waitKey(30);
	}
}