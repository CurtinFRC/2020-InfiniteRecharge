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

void DrivetrainAuto::WayPointSwitch() {
  _drivetrain.GetConfig().leftDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().rightDrive.encoder->ZeroEncoder();
  _drivetrain.GetConfig().gyro->Reset();
  AutoWaypointSwitcher++;
}


// ----------------------Auto------------------------


void DrivetrainAuto::OnUpdate(double dt) {
  std::cout << "Distance to target: " << _wayFinder.GetDistanceInRotations() << std::endl;
  switch (_autoSelector) {
    case 1: // Auto 1 (8 Ball)
      switch (AutoWaypointSwitcher) {
        case 1: // Start to Waypoint 1
          if (!_StartDoComplete) {break;} // If Something at the start of the match hasn't been completed yet
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(3.2, -2.4, 0, 5.4, -0.7, -90, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 2: // Drive from waypoint 1 to 2
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(5.4, -0.7, 0, 9.7, -0.7, 0, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 3: // Drive From waypoint 2 to 3 (Backwards)
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(9.7, -0.7, 0, 8, -0.7, -21.801, true, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 4: // Drive to endpoint (backwards)
      
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
}