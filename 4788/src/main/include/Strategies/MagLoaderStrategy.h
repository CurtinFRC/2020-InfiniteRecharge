#pragma once

#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "MagLoader2.h" // meant to be magloader2.h

using ButtonState = wml::controllers::Controller;

frc::Timer magTime;

class MagLoaderManualStrategy : wml::Strategy {
 public:
  MagLoaderManualStrategy(
    MagLoader &magLoader,
    wml::controllers::SmartControllerGroup &controllers
  ) : wml::Strategy("Manual"), _magLoader(magLoader), _controllers(controllers) {
    Requires(&magLoader);
    SetCanBeInterrupted(true);
    SetCanBeReused(true);
  }

  void OnUpdate(double dt) override {
    double magLoader_power = 0.7;

    if (_controllers.Get(ControlMap::ManualMag, ButtonState::ONRISE)) {
      if (MagLoaderOverride)
        MagLoaderOverride = false;
      else 
        MagLoaderOverride = true;
    }

    /**
     * MAIN MAG CONTROL
     */
    if (!MagLoaderOverride) {
      // Shift mag up (Stop mag if last sensor hit)
      if (_controllers.Get(ControlMap::ShiftUpMagazine)) 
        _magLoader.SetMagLoader(MagLoaderState::SHIFT, magLoader_power);

      // Shift mag down (Stop mag if index sensor hit)
      else if (_controllers.Get(ControlMap::ShiftDownMagazine))
        _magLoader.SetMagLoader(MagLoaderState::SHIFT, -magLoader_power);
      
      // Set to IDLE
      else 
        _magLoader.SetMagLoader(MagLoaderState::AUTO, magLoader_power);
      
    /**
     * OVERRIDE CONTROL
     */
    } else {
      // Shift up magazine
      if (_controllers.Get(ControlMap::ShiftUpMagazine))
        _magLoader.SetMagLoader(MagLoaderState::MANUAL, magLoader_power);

      // Shift down magazine
      else if (_controllers.Get(ControlMap::ShiftDownMagazine))
        _magLoader.SetMagLoader(MagLoaderState::MANUAL, -magLoader_power);

      // Set to IDLE
      else 
        _magLoader.SetMagLoader(MagLoaderState::MANUAL, 0);
    }


    // Fire balls
    if (_controllers.Get(ControlMap::TurretFire)) {
      magTime.Start();
      if (magTime.Get() > 0.2) {
        _magLoader.SetMagLoader(MagLoaderState::FIRE, magLoader_power);
        magTime.Reset();
      }
    } else {
      magTime.Stop();
    }
  }


 private:
  const MagLoader &_magLoader;
  const wml::controllers::SmartControllerGroup &_controllers;
  
  bool MagLoaderOverride = false;
};