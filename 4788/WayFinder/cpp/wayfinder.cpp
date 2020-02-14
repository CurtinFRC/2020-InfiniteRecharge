#include "wayfinder.h"

using namespace std;
using namespace wml;

// Initilize way finder
WayFinder::WayFinder(double kp, double ki, double kd, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter) : _drivetrain(drivetrain) {
  _kP = kp;
  _kI = ki;
  _kD = kd;

  _GearRatio = gearboxReduction;
  _WheelDiameter = WheelDiameter;
}

// Calculate rotations to the waypoint target
double WayFinder::RotationsToTarget(double p1x, double p1y, double p2x, double p2y) {
  _DistanceInMeters = sqrt(pow(p2x - p1x, 2) + pow(p2y - p1y, 2) * 1.0);
  _DistanceInCM = _DistanceInMeters*100;

  double DistanceInRotations = _GearRatio * (_DistanceInCM/(M_PI * _WheelDiameter));

  return DistanceInRotations;
}

// Config for speed
void WayFinder::AutoConfig(double MaxSpeed, double MaxTurnSpeed) {
  _MaxSpeed = MaxSpeed;
  _MaxTurnSpeed = MaxTurnSpeed;
}

// Way finders internal PID
double WayFinder::InternalPID(double dt, double goal, double input) {
  double error = goal - input;
  double derror = (error - _previousError)/dt;

  _sum = _sum + error * dt;

  double output = _kP * error + _kI * _sum + _kD * derror;
  output = output > _MaxSpeed ? _MaxSpeed : output;
  return output;
}

// Inverse Numbers
double WayFinder::InverseNumber(double input) {
  input = input < 0 ? abs(input) : -input;
  return input;
}


// Using the provided PID and gyro, turn to the target
void WayFinder::TurnToTarget(double dt, double input, double goal, bool reverse) {
  double turnSpeed = (InternalPID(dt, goal, input) * _MaxTurnSpeed);
  if (reverse) {
    _drivetrain.Set(-turnSpeed, turnSpeed);
  } else {
    _drivetrain.Set(turnSpeed, -turnSpeed);
  }
}

// Get Average distance
double WayFinder::GetDistanceInRotations() {
  return _DistanceInRotations;
}


// Get Average Location
double WayFinder::GetDrivetrainCurrentLocation() {
  double CombinedLocation = (fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) + fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()));
  return CombinedLocation/2;
}


// Drive to the target waypoint
void WayFinder::DriveToTarget(double dt, double goal , bool reverse) {
  // Add power using PID
  double LeftSpeed = InternalPID(dt, goal, abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()));
  double RightSpeed = InternalPID(dt, goal, abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()));


  if (reverse) {
    // Drive straight using gyro
    LeftSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));
    RightSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));

    // Inverse Power
    LeftSpeed = InverseNumber(LeftSpeed);
    RightSpeed = InverseNumber(RightSpeed);
  } else {
    // Drive straight using gyro
    LeftSpeed -= (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));
    RightSpeed += (_drivetrain.GetConfig().gyro->GetAngle() * (_kP));
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

bool WayFinder::GetWayPointComplete() {
  if (WayPointComplete) {
    WayPointComplete = false;
    return true;
  } else {
    return false;
  }
}

void WayFinder::GotoWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse, double dt) {
  // Get the distance to the target in rotations
  _DistanceInRotations = RotationsToTarget(wypt1x, wypt1y, wypt2x, wypt2y);
  double CurrentAngle = _drivetrain.GetConfig().gyro->GetAngle();
  switch (CaseNumber) {
    case 1:
      // Turn to Start Angle
      if (abs(startAngle) > 0) {
        if (abs(CurrentAngle) < abs(startAngle)) {
          TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), startAngle, reverse);
        }
      } else {
        CaseNumber++;
        WayPointComplete = false;
      }
    break;

    case 2:
      // Drive to target
      if (abs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) < _DistanceInRotations || abs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) < _DistanceInRotations) {
        DriveToTarget(dt, _DistanceInRotations, reverse);
      } else {
        CaseNumber++;
        WayPointComplete = false;
      }
    break;

    case 3:
      // Turn to End Angle
      if (abs(endAngle) > 0) {
        if (abs(CurrentAngle) < abs(endAngle)) {
          TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), endAngle, reverse);
        } else {
          CaseNumber = 1;
          WayPointComplete = true;
        }
      } else {
        CaseNumber = 1;
        _drivetrain.Set(0, 0);
        WayPointComplete = true;
      }
    break;
  }
}