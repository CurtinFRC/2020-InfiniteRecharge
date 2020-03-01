#include "DriveSystem.h"

using namespace wml;
using namespace wml::controllers;

// Initializes & Defines groups for Autonomous driving
DrivetrainAuto::DrivetrainAuto(Drivetrain &drivetrain, 
                               WayFinder &wayFinder,
                               control::PIDGains gains,
                               actuators::DoubleSolenoid &ChangeGears,
                               actuators::DoubleSolenoid &Shift2PTO,
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
                               _ChangeGears(ChangeGears),
                               _Shift2PTO(Shift2PTO),
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

  // Config For WayFinder
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

  // Default State for gearing
  _ChangeGears.SetTarget(wml::actuators::BinaryActuatorState::kReverse);
  _Shift2PTO.SetTarget(wml::actuators::BinaryActuatorState::kReverse);

  std::cout << "Distance to target: " << _wayFinder.GetDistanceInRotations() << std::endl;
  switch (_autoSelector) {
    case 1: // Auto 1 (8 Ball)
      switch (AutoWaypointSwitcher) {
        case 1: // Start to Waypoint 1
          if (!_StartDoComplete) {break;} // If Something at the start of the match hasn't been completed yet, fires 3 balls
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(3.2, -2.4, -30, 5.4, -0.7, 30, false, dt);
          } else {
            WayPointSwitch();
            _p1 = true;
          }
        break;

        case 2: // Drive from waypoint 1 to 2
          if(!_p1) {break;}
          _wayFinder.AutoConfig(0.25, 0.25); // Adjust Speed for intaking
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(5.4, -0.7, 0, 9, -0.7, 0, false, dt);
          } else {
            WayPointSwitch();
            _p1 = false;
          }
        break;

        case 3:
          _wayFinder.AutoConfig(ControlMap::MaxAutoDrivetrainSpeed, ControlMap::MaxAutoTurnSpeed);
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(9, -0.7, 0, 8, -0.7, -21, true, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 4: // Drive From waypoint 2 to 3 (Backwards)
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(8, -0.7, 0, 4.2, -2.4, 21, true, dt);
          } else {
            WayPointSwitch();
          }
        break;
       
        case 6: //shoot 5 balls 
          _strt = true;
        break;
      }
    break;


    case 2: // auto 2, 6 ball 
      switch(AutoWaypointSwitcher) { // shoots 3 balls at the very beginning of the match 
        case 1:
          if (!_StartDoComplete) {break;}
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(3.2, -2.4, -35, 5.4, -0.7, 35, false, dt);
          } else {
            WayPointSwitch();
            _p1 = true;
          }
        break;
          
        case 2:
          if (!_p1) {break;}
          if (!_wayFinder.GetWayPointComplete()) {
              _wayFinder.GotoWaypoint(5.4, -0.7, 0, 8, -0.7, -21, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 3:
          _p1 = false;
        break;

        case 4:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(8, -0.7, 0, 4.2, -2.4, 21, true, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 5:
          _strt = true;
        break;
      }
    break;


    case 4: // Auto 4, 3 ball left posision 
      switch(AutoWaypointSwitcher) {
        case 1:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint(3.2 , -2.4, 0, 4.1, -2.3, -180 ,  true, dt);
          } else {
             WayPointSwitch();
          }
        break;

        case 2:
          _strt = true;
        break;
      }
    break;


    case 3: // Auto 3, 3 ball at middle posision
      switch(AutoWaypointSwitcher) {
        case 1:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint( 3.2, -4, 0, 4.3, -4, -90, false, dt);
          } else {
            WayPointSwitch();
          }
        break;
        
        case 2:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint( 4.3, -4, 0, 4.3, -2.3, -90, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 3:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint( 4.3, -2.3, 0, 3, -2.3, 0, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 4: 
          _strt = true;
        break;
      }
    break;


    case 5: // Auto 5, 3 ball posison righht
      switch(AutoWaypointSwitcher) {
        case 1:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint( 3.2, -6, 0, 4.3, -6 , -90, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 2: 
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint( 4.3, -6, 0, 4.3, -2.4, -90, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 3:
          if (!_wayFinder.GetWayPointComplete()) {
            _wayFinder.GotoWaypoint( 4.3, -2.4, 0, 3.4, -2.4, 0, false, dt);
          } else {
            WayPointSwitch();
          }
        break;

        case 4:
          _strt = true;
        break;
      }
    break;
  }
  _ChangeGears.Update(dt);
  _Shift2PTO.Update(dt);
}