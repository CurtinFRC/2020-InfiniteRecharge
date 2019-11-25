#pragma once

#include "GeneralLibs/GeneralLibs.h"
#include "ControlMap.h"
#include "RobotMap.h"

class SubSystem1 {
  public:

    // ----------------Instances--------------------
    ControlMap *controlMap;

    // -------------Function Definement----------------
    SubSystem1(RobotMap &robotMap);
    void zeroEncoder();
    void SubSystem1Control();
    
  private:
    RobotMap *_robotmap;
};