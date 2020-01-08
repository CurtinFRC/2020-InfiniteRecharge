#pragma once 

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "Drivetrain.h"

class DrivetrainManual : public wml::Strategy {
  public:
    DrivetrainManual(std::string name, wml::Drivetrain &drive, wml::controllers::SmartController &cont1, wml::controllers::SmartController &cont2);

    void OnUpdate(double dt) override;

  private:
    wml::Drivetrain &_drivetrain;
    wml::controllers::SmartController &_cont1, &_cont2;
};