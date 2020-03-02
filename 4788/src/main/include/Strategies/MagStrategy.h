#include "controllers/Controllers.h"
#include "strategy/Strategy.h"
#include "MagLoader.h"

class MagManualStrategy : wml::Strategy {
  public:
    MagManualStrategy(
      const Mag &mag,
      const wml::controllers::SmartControllerGroup &controllers,
    ) : wml::Strategy("Manual"), _mag(mag), _controllers(controllers) {
      Requires(&mag);
      SetCanBeInterrupted(true);
      SetCanBeReused(true);
    }

    void OnUpdate(double dt) override {
      
    }


    private:
      const Mag &_mag;
      const wml::controllers::SmartControllerGroup &_controllers;
};