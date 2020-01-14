#pragma once

#include <string>
#include <utility>

#include "devices/StateDevice.h"
#include "Gearbox.h"
#include "sensors/BinarySensor.h"
#include "RobotMap.h"

struct TurretConfig {
	wml::Gearbox &horizontalAxis;		// WIP - type needs to be changed
	wml::Gearbox &verticalAxis;  		// WIP - type needs to be changed

	wml::sensors::BinarySensor *limitSensorHorizontal;
	wml::sensors::BinarySensor *limitSensorVertical;

	std::string name = "<Turret>";
};

enum class TurretState { kManual = 0, kSetpoint, kZeroing };
class Turret : public wml::devices::StateDevice<TurretState> {
 public:
	Turret(TurretConfig config) : StateDevice(config.name), _config(config) {};

	virtual std::string GetStateString() final;

	void SetManual(double power);
	void SetSetpoint(double setpoint);
	void SetZeroing();

	std::pair<double, double> GetSetpoint() { return _setpoint; };

	TurretConfig &GetConfig() { return _config; };
	
 protected:
	virtual void OnStatePeriodic(TurretState state, double dt) override;

 private:
	TurretConfig _config;
	std::pair<double, double> _setpoint;
	// is this private. OR is it "private" or is this
};