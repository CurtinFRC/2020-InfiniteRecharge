#pragma once

#include <string>

#include "devices/StateDevice.h"
#include "Gearbox.h"

struct ShooterConfig {
	wml::Gearbox &flywheel;
	wml::Gearbox *feeder;

	std::string name = "<Shooter>";
};

enum class ShooterState { kIdle = 0, kCharging, kFiring };
class Shooter : public wml::devices::StateDevice<ShooterState> {
 public:
	Shooter(ShooterConfig config) : StateDevice(config.name), _config(config) {};

	virtual std::string GetStateString() final;

	void SetIdle(double power);
	void SetCharging(double setpoint);
	void SetFiring();

	double GetSetpoint() { return _setpoint; };

	ShooterConfig &GetConfig();
	
 protected:
	virtual void OnStatePeriodic(ShooterState state, double dt) override;

 private:
	ShooterConfig _config;
	double _setpoint;
	// no uno
};