# 2020-InfiniteRecharge
### Code: [![Build Status](https://dev.azure.com/ConnorBuchel0890/ConnorBuchel/_apis/build/status/CurtinFRC.2020-InfiniteRecharge?branchName=master)](https://dev.azure.com/ConnorBuchel0890/ConnorBuchel/_build/latest?definitionId=9&branchName=master)

### Our code for the FRC game Infinite Recharge. Using multiproject gradle with wml gradle libraries from (https://github.com/wml-frc) supporting vision tracking and simulation support

# Quick Commands
## Build
`./gradlew :4788:build`, `./gradlew :TestBot:build`, or `./gradlew :4788:src:coprocessor:build`,
Build will compile and get the code ready without deploying it. It will also run all automated tests, which is great for testing your code before it ever gets run on a robot (which also means you can build whenever)

## Deploy
`./gradlew :4788:deploy`, `./gradlew :4788:src:coprocessor:deploy`, or `./gradlew :TestBot:deploy`  
Deploying will build your code (as above), and deploy it to the robot. You have to be connected to the robot for this to work. Just keep in mind that deploying _does not run any automated tests_.

## Simulation
`./gradlew sim4788`, or `./gradlew simTestBot`
Simulation will boot up a simulation of the robot code running on your own computer. This is used to see code running without a working robot, and includes a few simulation hooks for things like a tank drive and motor outputs.

NOTE: If you're running on Linux or MacOS, you should run `killall frcUserProgram` between calls to this. On windows, just ensure the command window that pops up is closed between runs. You can only have one simulator running at once!

## Running Vision
`./gradlew runVision`  
You can run vision on your local computer without needing a Raspberry Pi or Tinker Board to test on. As long as you have an external webcam, you should be A OK.

# Projects

## [4788](4788)
This is the team code. The code in these projects should be _very minimal_, since most will be put into `common`. This code should only initialize the layout / configuration of the robot and hand off most control to `commonRobot`. This allows us to share code between the two teams.

4788 both depend on `wml`.


## [WML](https://github.com/wml-frc/WML)
WML is the library for robot code on the RoboRio, designed to simplify FRC programming, and give usefull functions to use. Effectively replacing the normal frc:: with wml::

## [CJ-Vision](https://github.com/wml-frc/CJ-Vision)
CJ-Vision is the pre-threaded library used to power our vision tracking with nifty functions used often in frc vision tracking.

## [Vision](4788/src/coprocessor/)
Vision is the code that gets put on our vision system for the competition. Vision doesn't get deployed to the RoboRIO, but instead to a Raspberry Pi or Asus Tinkerboard.