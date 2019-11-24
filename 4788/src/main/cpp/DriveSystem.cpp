#include "ControlMap.h"
#include "DriveSystem.h"


DriveSystem::DriveSystem(int SRXportL_, int SRXportR_, int SPXportL_, int SPXportR_) {

  // Initialise Drive Motors
  DriveMotorLsrx = new curtinfrc::TalonSrx(SRXportL_);
  DriveMotorRsrx = new curtinfrc::TalonSrx(SRXportR_);
  DriveMotorLspx = new curtinfrc::VictorSpx(SPXportL_);
  DriveMotorRspx = new curtinfrc::VictorSpx(SPXportR_);

  // Zero Encoders (Only SRX's Have encoders)
  DriveMotorLsrx->ZeroEncoder();
  DriveMotorRsrx->ZeroEncoder();
}