#pragma once

#include "controllers/Controllers.h"
#include "RobotMap.h"

class MagLoader {
  public:
    MagLoader(wml::Gearbox &MagazineMotors, 
              frc::AnalogInput &StartMag, 
              frc::AnalogInput &Position1, 
              frc::AnalogInput &Position5, 
              wml::controllers::SmartControllerGroup &contGroup,
              int &autoSelector,
              bool &StartDoComplete,
              bool &strt,
              bool &p1,
              bool &p2,
              bool &p3,
              bool &end);

    void TeleopOnUpdate(double dt);
    void AutoOnUpdate(double dt);
    void TestOnUpdate(double dt);

  private:
    wml::Gearbox &_MagazineMotors;
    frc::AnalogInput &_StartMag;
    frc::AnalogInput &_Position1;
    frc::AnalogInput &_Position5;
    wml::controllers::SmartControllerGroup &_contGroup;

    // Network table
    nt::NetworkTableEntry MagPower;
    nt::NetworkTableEntry MagEncoder;
    nt::NetworkTableEntry StartSensor;
    nt::NetworkTableEntry SecondSensor;
    nt::NetworkTableEntry LastSensor;
    nt::NetworkTableEntry Override;

    // Auto Ball detection (Magazine control)
    void AutoMag();

    bool ToggleEnabled;
    bool MagOverride = false;
    double MagazinePower = 0;
    int MagStop = 1;

		int &_autoSelector;
		bool &_StartDoComplete;
		bool &_strt;
		bool &_p1;
		bool &_p2;
		bool &_p3;
		bool &_end;

    int BallTime3Shoot = 1.5;
		int BallTime5Shoot = 2.5;
		int SpinUpTime = 1;
		int autoAimTime = 2;
		int Ball3Shoot = BallTime3Shoot + SpinUpTime + autoAimTime; //time to shoot 3 balls
		int Ball5Shoot = BallTime5Shoot + SpinUpTime + autoAimTime; //shoots 5 balls 

    int testType = 1;
    frc::Timer timer;
};