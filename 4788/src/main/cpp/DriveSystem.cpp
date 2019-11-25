#include "DriveSystem.h"
#include "ControlMap.h"
#include "Robot.h"

DriveSystem::DriveSystem(int SRXportL_, int SRXportR_, int SPXportL_, int SPXportR_) {

  // We invert one side of the motors to make it drive straight when both sides are positively/negatively active

  // Initialise Drive Motors
  DriveMotorLsrx = new curtinfrc::TalonSrx(SRXportL_);
  DriveMotorLspx = new curtinfrc::VictorSpx(SPXportL_);
  DriveMotorLsrx->SetInverted(true);
  DriveMotorLspx->SetInverted(true);

  DriveMotorRsrx = new curtinfrc::TalonSrx(SRXportR_);
  DriveMotorRspx = new curtinfrc::VictorSpx(SPXportR_);
  DriveMotorRsrx->SetInverted(false);
  DriveMotorRspx->SetInverted(false);

  DriveSystem::zeroEncoder();
}

void DriveSystem::zeroEncoder() {
  // Zero Encoders (Only SRX's Have encoders)
  DriveMotorLsrx->ZeroEncoder();
  DriveMotorRsrx->ZeroEncoder();
}

void DriveSystem::DriveControl() {
}