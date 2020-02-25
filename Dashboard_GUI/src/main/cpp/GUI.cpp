#include "GUI.h"
#include "Dashboard/Orientation.h"

void GUI_Core::GUI(int argc, char** argv) {

  cv::Mat image; // Gui image (Made in paint... so what?)
  // Create Window/ Select Automode
  window = CreateWindow(image, argc, argv);

  // Initalize connection
  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("Autonomous");
  AutoSelector = table->GetEntry("AutoSelector");
  inst.StartClientTeam(4788);

  while (true) {
    AutoSelector.SetDouble(Auto);

    centerInfo.CentralInfoImage(&window, &inst, WidthHalf, HeightHalf);
    mag.MagLoader(&window, &inst, LeftUpperQuarterX, LeftUpperQuarterY);
    turret.TurretImage(&window, &inst, RightUpperQuarterX, RightUpperQuarterY);
    drive.DriveImage(&window, &inst, RightLowerQuarterX, RightLowerQuarterY);
    climber.ClimberImage(&window, &inst, LeftLowerQuarterX, LeftLowerQuarterY);

    DisplayWindow(window);
  }
}