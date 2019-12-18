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

void func(int *x) {
	*x = *x + 500;
}

void curtin_frc_vision::run() {
	int prtNumber = 1;

	func(&prtNumber);
	std::cout << &prtNumber;
}