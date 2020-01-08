#include "Climber.h"

using hand = frc::XboxController::JoystickHand;

void Robot::RobotInit()    {
    // Controller
    xbox = new frc::XboxController(0);

    // Climbing motor
    climb[0] = new frc::Spark(0);   // Set motor control to port 0 for testing
}

void Robot::DisabledInit()  {
    InterruptAll(true); // Emergency Stop (I assume)
}

void Robot::TeleopPeriodic()  {
    if (xbox->GetAButton()) {   // Pressing the A button extends the appendage
        climb[0]->Set(0.5);
    } else if (xbox->GetBButton()) {   // Pressing the B button retracts the appendage
        climb[0]->Set(-0.5);
    } else  {
        climb[0]->Set(0);
    }
}