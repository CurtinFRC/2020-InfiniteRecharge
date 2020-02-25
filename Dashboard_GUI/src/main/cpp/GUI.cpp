#include "GUI.h"
#include "Dashboard/Orientation.h"

void GUI_Core::GUI () {

  // Create Window/ Select Automode
  window = CreateWindow();

  // Initalize connection
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Autonomous");
  AutoSelector = table->GetEntry("AutoSelector");
  inst.StartClientTeam(4788);


  while (true) {
    AutoSelector.SetDouble(Auto);
    mag.MagLoader(&window, &inst, LeftUpperQuarterX, LeftUpperQuarterY);
    turret.TurretImage(&window, &inst, RightUpperQuarterX, RightUpperQuarterY);
    drive.DriveImage(&window, &inst, RightLowerQuarterX, RightLowerQuarterY);
    climber.ClimberImage(&window, &inst, LeftLowerQuarterX, LeftLowerQuarterY);

    DisplayWindow(window);
  }
}