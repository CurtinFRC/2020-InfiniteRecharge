#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, 
                               control::PIDGains gains,
                               int &autoSelector,
                               bool &strt,
                               bool &p1,
                               bool &p2,
                               bool &p3,
                               bool &end) : 
                               
                               _drivetrain(drivetrain), 
                               _pid(gains),
                               _autoSelector(autoSelector),
                               _strt(strt),
                               _p1(p1),
                               _p2(p2),
                               _p3(p3),
                               _end(end) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);
}

void Rotation2Point(double *DistanceInRotations, double p1x, double p1y, double p2x, double p2y) {}

double leftPreviousError = 0;
double rightPreviousError = 0;
double leftSum = 0;
double rightSum = 0;

double AutoPID(double dt, double goal, double input, double kp, double ki, double kd, double *previousError, double *sum) {
  double error = goal - input;
  double derror = (error - *previousError) / dt;
  *sum = *sum + error * dt;  

   double output = kp * error + ki * *sum + kd * derror;

  *previousError = error;
  return output;
} 

void DriveToTarget(double *leftPower, double *right, double DistanceInRotations) {
  leftPower = AutoPID(dt, 
                              DistanceInRotations, 
                              _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations(), 
                              ControlMap::leftKp,
                              ControlMap::leftKi,
                              ControlMap::leftKd,
                              &leftPreviousError,
                              &leftSum);
  rightPower = AutoPID(dt, 
                               DistanceInRotations, 
                               _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations(),
                               ControlMap::rightKp,
                               ControlMap::rightKi,
                               ControlMap::rightKd,
                               &rightPreviousError,
                               &rightSum);
}

void DrivetrainAuto::OnUpdate(double dt) {
  double leftPower, rightPower;
  double DistanceInRotations;
  switch (_autoSelector) {
    case 1: // Auto 1
      Rotation2Point(&DistanceInRotations, ControlMap::Strt6Ballx, ControlMap::Strt6Bally, ControlMap::wypt1Ball8x, ControlMap::wypt1Ball8y);
      if (!_strt) {
        if ((_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() < DistanceInRotations) || (_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() < DistanceInRotations)) {
          leftPower = AutoPID(dt, 
                              DistanceInRotations, 
                              _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations(), 
                              ControlMap::leftKp,
                              ControlMap::leftKi,
                              ControlMap::leftKd,
                              &leftPreviousError,
                              &leftSum);
          rightPower = AutoPID(dt, 
                               DistanceInRotations, 
                               _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations(),
                               ControlMap::rightKp,
                               ControlMap::rightKi,
                               ControlMap::rightKd,
                               &rightPreviousError,
                               &rightSum);
        } else {
          _strt = true;
        }
      }
      break;
    case 2: // Auto 2

      break;
    case 3: // Auto 3

      break;
    case 4: // Auto 4

      break;
    case 5: // Auto 5
      break;
  }
  _drivetrain.Set(leftPower, rightPower);
}