#pragma once 

#include "strategy/StrategySystem.h"
#include "RobotMap.h"

enum class IntakeDownState { 
  IDLE,
  MANUAL
};

enum class IntakeMovingState {
  IDLE,
  MANUAL
};

class Intake : public wml::StrategySystem {
  public:
    Intake(wml::Gearbox &BeltIntakeMotors,
           wml::actuators::DoubleSolenoid &IntakeDown);

  void SetDown(const IntakeDownState) {

  } 

  void SetMove(const IntakeMovingState) {

  }

  void UpdateSetMove(double dt) {

  }

  void UpdateSetDown(double dt) {

  }

  void Update(double dt) {
    UpdateSetDown();
    UpdateSetMove();
  }
}