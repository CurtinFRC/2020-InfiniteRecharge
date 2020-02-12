#include "wayfinder.h"

using namespace std;
using namespace wml;

WayFinder::WayFinder(double kp, double ki, double kd, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter) : _drivetrain(drivetrain) {
  _kP = kp;
  _kI = ki;
  _kD = kd;

  _GearRatio = gearboxReduction;
  _WheelDiameter = WheelDiameter;
}

double WayFinder::RotationsToTarget(double p1x, double p1y, double p2x, double p2y) {
  _DistanceInMeters = sqrt(pow(p2x - p1x, 2) + pow(p2y - p1y, 2) * 1.0);
  _DistanceInCM = _DistanceInMeters*100;

  double DistanceInRotations = _GearRatio * (_DistanceInCM/(M_PI * _WheelDiameter));

  return DistanceInRotations;
}

void WayFinder::AutoConfig(double MaxSpeed, double MaxTurnSpeed) {
  _MaxSpeed = MaxSpeed;
  _MaxTurnSpeed = MaxTurnSpeed;
}

double WayFinder::InternalPID(double dt, double goal, double input) {
  double error = goal - input;
  double derror = (error - _previousError)/dt;
  _sum = _sum + error * dt;

  double output = _kP * error + _kI * _sum + _kD * derror;
  return output; 
}

// Inverse Numbers
double WayFinder::InverseNumber(double input) {
  input = input < 0 ? abs(input) : -input;
  return input;
}


// Using the provided PID and gyro, turn to the target
void WayFinder::TurnToTarget(double dt, double input, double goal) {
  double turnSpeed = InternalPID(dt, goal, input) * _MaxTurnSpeed;

  _drivetrain.Set(turnSpeed, -turnSpeed);
}


void WayFinder::DriveToTarget(double dt, double goal , bool reverse) {

  // Add power using PID
  double LeftSpeed = InternalPID(dt, goal, _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());
  double RightSpeed = InternalPID(dt, goal, _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());

  // Drive straight using gyro
  LeftSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * (_kP/2));
  RightSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * (_kP/2));

  // Invert Values if reverse
  if (reverse) {
    InverseNumber(LeftSpeed);
    InverseNumber(RightSpeed);
  }

  // Limit Power to max speed
  LeftSpeed *= _MaxSpeed;
  RightSpeed *= _MaxSpeed;

  // Set Speed
  _drivetrain.Set(LeftSpeed, RightSpeed);
}

void WayFinder::TestPID(double dt, double goal) {
  // Add power using PID
  double LeftSpeed = InternalPID(dt, goal, _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());
  double RightSpeed = InternalPID(dt, goal, _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());

  // Drive straight using gyro
  LeftSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * (_kP/2));
  RightSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * (_kP/2));

  // Limit Power to max speed
  LeftSpeed *= _MaxSpeed;
  RightSpeed *= _MaxSpeed;

  // Set Speed
  _drivetrain.Set(LeftSpeed, RightSpeed);
}

void WayFinder::GotoWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse) {
  // Get the distance to the target in rotations
  _DistanceInRotations = RotationsToTarget(wypt1x, wypt1y, wypt2x, wypt2y);

  // Turn to Start Angle
  if (abs(startAngle) > 0) {
    TurnToTarget(_dt, _drivetrain.GetConfig().gyro->GetAngle(), startAngle);
  }

  // Drive to target
  if (abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) < _DistanceInRotations || abs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) < _DistanceInRotations) {
    if (reverse) {
      DriveToTarget(_dt, _DistanceInRotations, reverse);
    }
  }

  // Turn to End Angle
  if (abs(endAngle) > 0) {
    TurnToTarget(_dt, _drivetrain.GetConfig().gyro->GetAngle(), endAngle);
  }
}