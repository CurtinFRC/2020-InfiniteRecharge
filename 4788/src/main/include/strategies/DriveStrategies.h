#pragma once

#include "Drivetrain.h"

#include "strategy/Strategy.h"
#include "controllers/Controllers.h"

class DrivetrainManualStrategy : public wml::Strategy {
 public:
  DrivetrainManualStrategy(std::string name, wml::Drivetrain &drive, wml::controllers::SmartController &cont1, wml::controllers::SmartController &cont2);

  void OnUpdate(double dt) override;

 private:
  wml::Drivetrain &_drivetrain;
  wml::controllers::SmartController &_cont1, &_cont2;
};
