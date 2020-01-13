#include "vision.h"
#include <iostream>

double offsetX, offsetY;
int ResWidth = 640, ResHeight = 480;

double cx, cy;

cv::Mat Image; // Origin Image
cv::Mat TrackingImage; // Imaged After it has been procesed
cv::Mat ProcessingOutput;

void curtin_frc_vision::run() {
	auto inst = nt::NetworkTableInstance::GetDefault();
	auto visionTable = inst.GetTable("VisionTracking");
	auto table = visionTable->GetSubTable("Target");

	TargetX = table->GetEntry("Target_X");
	TargetY = table->GetEntry("Target_Y");
	ImageHeight = table->GetEntry("ImageHeight");
	ImageWidth = table->GetEntry("ImageWidth");

	inst.StartClientTeam(4788);

	vision.SetupVision(&Image, 4, 30, ResHeight, ResWidth, 1, "Turret Cam", true);
	vision.CustomTrack(&TrackingImage, &Image, 30, 70, 50, 255, 0, 0);
	vision.Processing.visionHullGeneration.BoundingBox(&TrackingImage, &ProcessingOutput, &cx, &cy, 10);
	#ifdef __DESKTOP__ 
	std::cout << "Exposure Might be dissabled on local machine" << std::endl;
	#else
	system("v4l2-ctl -d /dev/video4 --set-ctrl=exposure_absolute=1");
	#endif

	std::cout << "Vision Tracking Process Running" << std::endl;
	while (true) {
		if (vision.Camera.cam.sink.GrabFrame(Image) != 0) {

			// Vision Outputing
			#ifdef __DESKTOP__
			vision.Output.Display("Origin Image", &Image);
			vision.Output.Display("Green Filtered Image", &TrackingImage);
			vision.Output.Display("Contour Detection", &ProcessingOutput);
			#else 
			vision.Camera.cam.output.PutFrame(Image); // Might get rid of this to speed up loop.
			#endif

			//Calc offset
			offsetX = cx-(ResWidth/2);
			offsetY = cy-(ResHeight/2);
			
			// Sending Values to nt
			visionTable->PutNumber("X Offset", offsetX);

			TargetX.SetDouble(offsetX);
			TargetY.SetDouble(offsetY);
			ImageHeight.SetDouble(ResHeight);
			ImageWidth.SetDouble(ResWidth);
			visionTable->PutBoolean("Vision Active", true);
		} else {
			visionTable->PutBoolean("Vision Active", false);
		}
	}
}