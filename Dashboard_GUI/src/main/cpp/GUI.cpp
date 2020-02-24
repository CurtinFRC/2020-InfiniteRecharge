#include "GUI.h"
#include "Dashboard/Orientation.h"

void GUI_Core::GUI () {

  window = CreateWindow();

  while (true) {
    mag.MagLoader(&window, LeftUpperQuarterX, LeftUpperQuarterY);
    turret.TurretImage(&window, RightUpperQuarterX, RightUpperQuarterY);
    drive.DriveImage(&window, RightLowerQuarterX, RightLowerQuarterY);
    climber.ClimberImage(&window, LeftLowerQuarterX, LeftLowerQuarterY);

    DisplayWindow(window);
  }
}