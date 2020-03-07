#include "vision.h"
#include <iostream>
// #include <windows.h>

double offsetX, offsetY;
int ResWidth = 640, ResHeight = 480;

cv::Point RotationLineStrt(320, 0);
cv::Point RotationLineEnd(320, 480);

double cx, cy;
double AverageCX;
double AverageCY;

double SampleX[10];
double SampleY[10];
double SampleXAcumulator = 0;
double SampleYAcumulator = 0;
int sampleCounter = 0;

double lastCX = 0;

cv::Mat Image; // Origin Image
cv::Mat TrackingImage; // Imaged after it has been filtered
cv::Mat ProcessingOutput; // Image after is has been processed

void curtin_frc_vision::run() {
	auto inst = nt::NetworkTableInstance::GetDefault();
	auto visionTable = inst.GetTable("VisionTracking");
	auto table = visionTable->GetSubTable("Target");

	TargetX = table->GetEntry("Target_X");
	TargetY = table->GetEntry("Target_Y");
	ImageHeight = table->GetEntry("ImageHeight");
	ImageWidth = table->GetEntry("ImageWidth");

	inst.StartClientTeam(4788);


	vision.SetupVision(&Image, 0, 60, ResHeight, ResWidth, 1, "Turret Cam", true);
	vision.CustomTrack(&TrackingImage, &Image, 50, 70, 250, 255, 30, 255, 1 ,1);
	vision.Processing.visionHullGeneration.BoundingBox(&TrackingImage, &ProcessingOutput, &cx, &cy, 10);
	#ifdef __DESKTOP__ 
	std::cout << "Exposure Might be dissabled on local machine" << std::endl;
	#else
	system("v4l2-ctl -d /dev/video0 --set-ctrl=exposure_absolute=1");
	#endif
	std::cout << "Vision Tracking Process Running" << std::endl;
	while (true) {
		if (vision.Camera.cam.sink.GrabFrame(Image) != 0) {
		
			offsetX = cx-(ResWidth/2);
			offsetY = cy; // Don't need offset. We're using setpoints

			// SampleX[sampleCounter] = offsetX;
			// SampleY[sampleCounter] = offsetY;
			// SampleXAcumulator += SampleX[sampleCounter];
			// SampleYAcumulator += SampleY[sampleCounter];
			// sampleCounter++;


			// if (sampleCounter > 10) {
			// 	SampleXAcumulator /= 10;
			// 	SampleYAcumulator /= 10;
			// 	AverageCX = SampleXAcumulator;
			// 	AverageCY = SampleYAcumulator;
			// 	sampleCounter = 0;
			// }

			// Display Image
			cv::line(ProcessingOutput, RotationLineStrt, RotationLineEnd, cv::Scalar(255,0,255), 2);
			vision.Display("Output", &ProcessingOutput);

			visionTable->PutBoolean("Vision Active", true);

			TargetX.SetDouble(offsetX-5);
			TargetY.SetDouble(offsetY);
			ImageHeight.SetDouble(ResHeight);
			ImageWidth.SetDouble(ResWidth);
		} else {
			visionTable->PutBoolean("Vision Active", false);
		}
	}
}