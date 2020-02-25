#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "GUI.h"
#include <urlmon.h>
#include <tchar.h>
#pragma comment(lib, "urlmon.lib")

GUI_Core gui;
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
  std::cout << "Starting GUI" << std::endl;

  // Download image online
  std::cout << "Downloading gui image (if connected)" << std::endl;
  HRESULT hr = URLDownloadToFile(NULL, _T("https://drive.google.com/u/0/uc?id=1z2U5PHubFVGWhVz5UuFWeCdSyPxy4gxy&export=download"), _T("C:/Users/Public/DASH_GUI.png"), 0, NULL);

  gui.GUI(argc, argv);
  return 0;
}