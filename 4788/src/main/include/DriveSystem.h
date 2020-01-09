#pragma once 

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "Drivetrain.h"


// Class that Runs In Manual Drive e.g Human Drivers
class DrivetrainManual : public wml::Strategy {
  public:
    DrivetrainManual(std::string name, wml::Drivetrain &drive, wml::controllers::SmartControllerGroup &contGroup);

    void OnUpdate(double dt) override;

  private:
    wml::Drivetrain &_drivetrain;
    wml::controllers::SmartControllerGroup &_contGroup;
};

// Class that Runs in Autonomous
class DrivetrainAuto : public wml::Strategy {
  public:
    DrivetrainAuto(wml::Drivetrain &drive, wml::control::PIDGains);

    void OnUpdate(double dt) override;

  private:
    wml::Drivetrain &_drivetrain;
    wml::control::PIDController _pid;
};