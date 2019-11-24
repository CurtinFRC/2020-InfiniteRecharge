#include "Robot.h"
#include "DriveSystem.h"

DriveSystem::DriveSystem(int SRXportL_, int SRXportR_, int SPXportL_, int SPXportR_) {
  DriveMotorLsrx = new curtinfrc::TalonSrx(SRXportL_);
  DriveMotorRsrx = new curtinfrc::TalonSrx(SRXportR_);
  DriveMotorLspx = new curtinfrc::VictorSpx(SPXportL_);
  DriveMotorRspx = new curtinfrc::VictorSpx(SPXportR_);
}