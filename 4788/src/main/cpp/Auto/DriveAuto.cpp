#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, 
                               WayFinder &wayFinder,
                               control::PIDGains gains,
                               int &autoSelector,
                               bool &StartDoComplete,
                               bool &strt,
                               bool &p1,
                               bool &p2,
                               bool &p3,
                               bool &end) : 
                               
                               _drivetrain(drivetrain), 
                               _wayFinder(wayFinder),
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

  _wayFinder.AutoConfig(ControlMap::MaxAutoDrivetrainSpeed, ControlMap::MaxAutoTurnSpeed);
}


// ----------------------Auto------------------------


void DrivetrainAuto::OnUpdate(double dt) {
  

  switch (_autoSelector) {
    case 1: // Auto 1 (8 Ball)
      switch (AutoWaypointSwitcher) {
        case 1: // Start to Waypoint 1
          if (!_StartDoComplete) {break;} // If Something at the start of the match hasn't been completed yet
          _wayFinder.GotoWaypoint(3.2, -2.4, 0, 5.4, -0.7, 54.462, false, dt);
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