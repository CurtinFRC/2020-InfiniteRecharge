#pragma once

#include "Drivetrain.h"

class WayFinder {
  public:

    /**
     * Way Finder. The crappy version of pathfinder. BUT WITH NO TRAJECTORIES. because, it's week 6.
     * and i'm not in the mood to build that. Initialize by inputing your PID values & drivetrain along 
     * with your gearbox reduction & wheel diameter. note gearbox reduction is from motor to output rotations on the wheel (12:1). 
     */
    WayFinder(double kp, double ki, double kd, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter);



    /**
     * Configure the speeds and values of your auto (Defult is 0.5 & 0.4)
     */
    void AutoConfig(double MaxSpeed, double MaxTurnSpeed);



    /**
     * Using pathweaver or whatever you choose to calculate your waypoints, input the coords
     * (in meters) of your desired locations, your start x & y, and your ending x & y.
     * Also your desired starting angle (Usually zero) and your ending angle in degrees.  
     * Also choose to reverse drivetrain or not (Drive backwards)
     */
    void GotoWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse, double dt);

    /** 
     * Test Your Driving PID 
     * (if it gets to the desired goal with reasonable acuracy then the PID shouldn't need changing)
     */
    void TestPID(double dt, double goal);


    /**
     * Get's the static distance of the goal in rotations
     */
    double GetDistanceInRotations();


    /**
     * Get's the average location between the left and riht encoders
     * to grab the location of the drivetrain
     */
    double GetDrivetrainCurrentLocation();



  private:
    void LeftDriveToTarget(double dt, double goal);
    void RightDriveToTarget(double dt, double goal);
    void DriveToTarget(double dt, double goal, bool reverse);
    void TurnToTarget(double dt, double input, double goal);

    double RotationsToTarget(double p1x, double p1y, double p2x, double p2y);
    double InternalPID(double dt, double goal, double input);
    double InverseNumber(double input);

    // Drivetrain
    wml::Drivetrain &_drivetrain;
    double _MaxSpeed = 0.5;
    double _MaxTurnSpeed = 0.4;
    double _WheelDiameter = 0;
    double _GearRatio = 0;
    
    // Target Values
    double _DistanceInMeters = 0;
    double _DistanceInCM = 0;
    double _DistanceInRotations = 0;

    // PID
    double _goal = 0;
    double _previousError = 0;
    double _sum = 0;
    double _kP = 0;
    double _kI = 0;
    double _kD = 0;


};