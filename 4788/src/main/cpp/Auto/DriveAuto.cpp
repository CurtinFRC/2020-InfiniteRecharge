#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, 
                               control::PIDGains gains,
                               int &autoSelector,
                               bool &StartDoComplete,
                               bool &strt,
                               bool &p1,
                               bool &p2,
                               bool &p3,
                               bool &end) : 
                               
                               _drivetrain(drivetrain), 
                               _pid(gains),
                               _autoSelector(autoSelector),
                               _StartDoComplete(StartDoComplete),
                               _strt(strt),
                               _p1(p1),
                               _p2(p2),
                               _p3(p3),
                               _end(end) {
  Requires(&drivetrain);
  SetCanBeInterrupted(true);
  SetCanBeReused(false);

  // _wayFinder = new WayFinder(ControlMap::leftKp, ControlMap::leftKi, ControlMap::leftKd, &_drivetrain, ControlMap::AutoGearRatio, ControlMap::WheelDiameter);
}

double Rotation2Point(double p1x, double p1y, double p2x, double p2y) {

  double distanceInMeters = sqrt(pow(p2x - p1x, 2) + pow(p2y - p1y, 2) * 1.0);
  double DistanceInCM = distanceInMeters*100;

  double DistanceInRotations = ControlMap::AutoGearRatio * (DistanceInCM/ControlMap::WheelCircumference);

  return DistanceInRotations;
}

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
  std::cout << "Goal " << goal << std::endl;
  std::cout << "Output " << output << std::endl;
  return output;
} 

double InverseNumber (double input) {
  input = input <= 0 ? abs(input) : -input;
  return input;
}

double DrivetrainAuto::TurnToTarget(double dt, double input, double goal) {
  double error = goal - input;
  double derror = (error - TurnPreviousError) / dt;
  TurnSum = TurnSum + error * dt;
  double output = ControlMap::turnP * error + ControlMap::turnI * TurnSum + ControlMap::turnD * derror;
  output = (output/goal);
  output *= ControlMap::MaxAutoTurnSpeed;
  return output;
}

double DrivetrainAuto::LeftDriveToTarget(double dt, double goal) {
  double power;
  power = AutoPID(dt, 
                  DistanceInRotations,
                  goal, 
                  ControlMap::leftKp,
                  ControlMap::leftKi,
                  ControlMap::leftKd,
                  &leftPreviousError,
                  &leftSum);
  // double error = DistanceInRotations - fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations());
  // double output = error;
  // output /= DistanceInRotations;
  // output *= ControlMap::MaxAutoDrivetrainSpeed;
  // power /= fabs(DistanceInRotations);
  power = power < -ControlMap::MaxAutoDrivetrainSpeed ? -ControlMap::MaxAutoDrivetrainSpeed : 
  power > ControlMap::MaxAutoDrivetrainSpeed ? ControlMap::MaxAutoDrivetrainSpeed : 0;
  return power;
}

double DrivetrainAuto::RightDriveToTarget(double dt, double goal) {

  double power;
  power = AutoPID(dt, 
                  DistanceInRotations,
                  goal, 
                  ControlMap::rightKp,
                  ControlMap::rightKi,
                  ControlMap::rightKd,
                  &rightPreviousError,
                  &rightSum);
  // double error = DistanceInRotations - fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations());
  // double output = error;
  // output /= DistanceInRotations;
  // power /= fabs(DistanceInRotations);
  power = power < -ControlMap::MaxAutoDrivetrainSpeed ? -ControlMap::MaxAutoDrivetrainSpeed : 
  power > ControlMap::MaxAutoDrivetrainSpeed ? ControlMap::MaxAutoDrivetrainSpeed : 0;
  return power;
}



// ----------------------Auto------------------------


void DrivetrainAuto::OnUpdate(double dt) {
  CurrentHeading = (_drivetrain.GetConfig().gyro->GetAngle() * (ControlMap::rightKp/2));
  double encoderLeft = _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations();
  double encoderRight = _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations();
  switch (_autoSelector) {
    case 1: // Auto 1 (8 Ball)
      switch (AutoWaypointSwitcher) {
        case 1: // Start to Waypoint 1
          if (!_StartDoComplete) {break;} // If Something at the start of the match hasn't been completed yet
          DistanceInRotations = Rotation2Point(ControlMap::Strt8Ballx, ControlMap::Strt8Bally, ControlMap::wypt1Ball8x, ControlMap::wypt1Ball8y);
          if ( (fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) < DistanceInRotations) || ( fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) < DistanceInRotations) ) {
            LeftPower = LeftDriveToTarget(dt, fabs(encoderLeft));
            RightPower = LeftDriveToTarget(dt, fabs(encoderRight)) + CurrentHeading;
          } else {
            LeftPower = 0;
            RightPower = 0;
            _drivetrain.GetConfig().gyro->Reset();
            _strt = true;
            AutoWaypointSwitcher++;
          }
        break;

        case 2: // Turn to waypoint 2
          if (_drivetrain.GetConfig().gyro->GetAngle() < ControlMap::wypt1Ball8Angle) {
            std::cout << "This is working" << std::endl;
            LeftPower = TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), ControlMap::wypt1Ball8Angle);
            RightPower = -TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), ControlMap::wypt1Ball8Angle);
          } else {
            LeftPower = 0;
            RightPower = 0;
            _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().gyro->Reset();
            AutoWaypointSwitcher++;
          }
        break;

        case 3: // Drive From waypoint 1 to 2
          DistanceInRotations = Rotation2Point(ControlMap::wypt1Ball8x, ControlMap::wypt1Ball8y, ControlMap::wypt2Ball8x, ControlMap::wypt2Ball8y);
          if ( (fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) < DistanceInRotations) || ( fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) < DistanceInRotations) ) {
            LeftPower = LeftDriveToTarget(dt, fabs(encoderLeft));
            RightPower = RightDriveToTarget(dt, fabs(encoderRight)) + CurrentHeading;
          } else {
            LeftPower = 0;
            RightPower = 0;
            _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().gyro->Reset();
            _p1 = true;
            AutoWaypointSwitcher++;
          }
        break;

        case 4: // Drive from waypoint 2 to 3 (Backwards)
          DistanceInRotations = Rotation2Point(ControlMap::wypt2Ball8x, ControlMap::wypt2Ball8y, ControlMap::wypt3Ball8x, ControlMap::wypt3Ball8y);
          if ( (fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) < DistanceInRotations) || ( fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) < DistanceInRotations) ) {
            LeftPower = -LeftDriveToTarget(dt, encoderLeft) - CurrentHeading;
            RightPower = -RightDriveToTarget(dt, encoderRight);
          } else {
            LeftPower = 0;
            RightPower = 0;
            _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().gyro->Reset();
            _p2 = true;
            AutoWaypointSwitcher++;
          }
        break;

        case 5: // Turn to EndPoint
          if (_drivetrain.GetConfig().gyro->GetAngle() > ControlMap::wypt3Ball8Angle) {
            std::cout << "This is working" << std::endl;
            LeftPower = -TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), ControlMap::wypt1Ball8Angle);
            RightPower = TurnToTarget(dt, _drivetrain.GetConfig().gyro->GetAngle(), ControlMap::wypt1Ball8Angle);
          } else {
            LeftPower = 0;
            RightPower = 0;
            _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().gyro->Reset();
            _p3 = true;
            AutoWaypointSwitcher++;
          }
        break;
          
        case 6: // Drive to Endpoint (Backwards)
          DistanceInRotations = Rotation2Point(ControlMap::wypt3Ball8x, ControlMap::wypt3Ball8y, ControlMap::End8Ballx, ControlMap::End8Bally);
          if ( (fabs(_drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations()) < DistanceInRotations) || ( fabs(_drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations()) < DistanceInRotations) ) {
            LeftPower = -LeftDriveToTarget(dt, encoderLeft) - CurrentHeading;
            RightPower = -RightDriveToTarget(dt, encoderRight);
          } else {
            LeftPower = 0;
            RightPower = 0;
            _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
            _drivetrain.GetConfig().gyro->Reset();
            _end = true;
            AutoWaypointSwitcher++;
          }
        break;
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
  std::cout << "Encoder Left " << _drivetrain.GetConfig().leftDrive.encoder->GetEncoderRotations() << std::endl;
  std::cout << "Encoder Right " << _drivetrain.GetConfig().rightDrive.encoder->GetEncoderRotations() << std::endl; 
  std::cout << "Distance In Rotations " << DistanceInRotations << std::endl;
  std::cout << "Angle " << _drivetrain.GetConfig().gyro->GetAngle() << std::endl;
  _drivetrain.Set(LeftPower, RightPower);
}