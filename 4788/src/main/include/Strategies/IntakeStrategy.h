#include "controllers/Controller.h"
#include "strategy/Strategy.h"
#include "BIntake2.h"

class IntakeManualStrategy : wml::Strategy {
 public:
  IntakeManualStrategy(
    const Intake &intake,
    const wml::actuators::DoubleSolenoid &IntakeDown,
    const wml::controllers::SmartControllerGroup &controllers,
  ) : wml::Strategy("Manual"), _beltIntake(intake), _controllers(controllers) {
    Requires(&intake);
    SetCanBeInterrupted(true);
    SetCanBeReused(true);
  }

  void OnUpdate(double dt) override {
    double beltintake_power = ControlMap::doJoyDeadzone(_controllers.Get(ControlMap::Intake));
    
    if (_controllers.Get(ControlMap::DownIntake)) {
      _IntakeDown.SetTarget(wml::actuators::BinaryActuatorState::kForward);
    } else {
      
    }
    beltintake_power = ControlMap::
  }

 private:
  const BeltIntake &_beltIntake;
  const wml::actuators::DoubleSolenoid &_IntakeDown;
  const wml::controllers::SmartControllerGroup &_controllers;
}take.h
