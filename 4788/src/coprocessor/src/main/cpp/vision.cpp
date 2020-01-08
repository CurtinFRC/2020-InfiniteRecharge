#include "vision.h"
#include <iostream>

float height_offset, width_offset;
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

	vision.SetupVision(&Image, 1, 60, ResHeight, ResWidth, 30, "TestCam", true);
	vision.CustomTrack(&TrackingImage, &Image, 30, 70, 50, 255, 100, 0, 0);
	while (vision.Camera.cam.sink.GrabFrame(Image) == 0) {}
	vision.Processing.visionHullGeneration.BoundingBox(&TrackingImage, &ProcessingOutput, &cx, &cy);
	while (true) {
		if (vision.Camera.cam.sink.GrabFrame(Image) != 0) {
			vision.Output.Display("Origin Image", &Image);
			vision.Output.Display("Green Filtered Image", &TrackingImage);
			vision.Output.Display("Contour Detection", &ProcessingOutput);
			TargetX.SetDouble(cx);
			TargetY.SetDouble(cy);
		}
	}
}