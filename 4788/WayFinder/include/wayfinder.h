#pragma once

#include "Drivetrain.h"

class WayFinder {
  public:

    /**
     * Way Finder. The crappy version of pathfinder. BUT WITH NO TRAJECTORIES. because, it's week 6.
     * and i'm not in the mood to build that. Initialize by inputing your PID values & drivetrain along 
     * with your gearbox reduction & wheel diameter. note gearbox reduction is from motor to output rotations on the wheel (12:1). 
     */
    WayFinder(double kp, double ki, double kd, double &dt, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter);



    /**
     * Configure the speeds and values of your auto (Defult is 0.5 & 0.4)
     */
    void AutoConfig(double MaxSpeed, double MaxTurnSpeed);



    /**
     * Using pathweaver or whatever you choose to calculate your waypoints, input the coords
     * (in meters) of your desired locations, your start x & y, and your ending x & y.
     * Also your desired starting angle (Usually zero) and your ending angle.  
     * Also choose to drive reversed or not
     */
    void GotoWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse);


  private:
    void LeftDriveToTarget(double dt, double goal);
    void RightDriveToTarget(double dt, double goal);
    void TurnToTarget(double dt, double input, double goal);

    double RotationsToTarget();

    double InternalPID(double dt, double goal);

    // Drivetrain
    wml::Drivetrain &_drivetrain;
    double _MaxSpeed = 0.5;
    double _MaxTurnSpeed = 0.4;
    double _WheelDiameter;
    double _GearRatio;
    
    // Target Values
    double _DistanceInMeters;
    double _DistanceInCM;
    double _DistanceInRotations;

    // PID
    double _goal;
    double _previousError;
    double _kP;
    double _kI;
    double _kD;
    double &_dt;


};