#include "wayfinder.h"

using namespace std;
using namespace wml;

WayFinder::WayFinder(double kp, double ki, double kd, double &dt, wml::Drivetrain &drivetrain, double gearboxReduction, double WheelDiameter) : _dt(dt), _drivetrain(drivetrain) {
  _kP = kp;
  _kI = ki;
  _kD = kd;
}

void WayFinder::AutoConfig(double MaxSpeed, double MaxTurnSpeed) {
  _MaxSpeed = MaxSpeed;
  _MaxTurnSpeed = MaxTurnSpeed;
}

void WayFinder::GoToWaypoint(double wypt1x, double wypt1y, double startAngle, double wypt2x, double wypt2y, double endAngle, bool reverse) {

}