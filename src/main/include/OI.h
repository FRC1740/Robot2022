
#pragma once

namespace ConShuffleboard {
    constexpr char RobotTab[] = "Robot";
    constexpr char ClimberTab[] = "Climber";
    constexpr char DriveTrainTab[] = "DriveTrain";
    constexpr char LauncherTab[] = "Launcher";
    constexpr char VisionTab[] = "Vision";
}

namespace ConFlightControl {
    // Axes
    constexpr int AILERON = 0;
    constexpr int ELEVATOR = 1;
    constexpr int RUDDER = 2;
    constexpr int TRIM = 3;
    // Buttons
    constexpr int TRIGGER = 0;
}

namespace ConXBOXControl {
    // Axis inputs
    constexpr int LEFT_JOYSTICK_X = 0;
    constexpr int LEFT_JOYSTICK_Y = 1;
    constexpr int LEFT_TRIGGER = 2;
    constexpr int RIGHT_TRIGGER = 3;
    constexpr int RIGHT_JOYSTICK_X = 4;
    constexpr int RIGHT_JOYSTICK_Y = 5;
    // Buttons
    constexpr int A = 1;
    constexpr int B = 2;
    constexpr int X = 3;
    constexpr int Y = 4;
    constexpr int LEFT_BUMPER = 5;
    constexpr int RIGHT_BUMPER = 6;
    constexpr int SELECT = 7;
    constexpr int START = 8;
    constexpr int LEFT_JOYSTICK = 9;
    constexpr int RIGHT_JOYSTICK = 10;

    // Dead zone
    constexpr double DEAD_ZONE = 0.1;

    // Driver controller Port
    constexpr int DRIVER_CONTROLLER_PORT = 0;
}

// DeadZone lambda function
auto DeadZone = [] (double value) { return (std::fabs(value) > ConXBOXControl::DEAD_ZONE) ? value : 0.0; };

// Texas Instruments Controller (MSP430F5529 LaunchPad)
namespace ConLaunchPad {
    namespace Button {
        constexpr int RED = 1;  // Jumble Fwd
        constexpr int BLUE = 2; // Jumble Rev
        constexpr int YELLOW = 3; // Not Used (Climber?)
        constexpr int GREEN = 4; // Not Used (Climber?)
        constexpr int WHITE = 5; // Climber Unlock (Hold to unlock)
    }

    namespace Switch {
        constexpr int RED = 6;
        constexpr int BLUE = 7;
        constexpr int YELLOW = 8;
        constexpr int GREEN = 9; // Reset/Disable Climber Encoder
    }

    namespace Dial {
        constexpr int LEFT = 2;
        constexpr int RIGHT = 6;
    }

    constexpr int SLIDER = 42; // Unknown axis
    constexpr int LEFT_STICK_X = 1; 
    constexpr int LEFT_STICK_Y = 0;

    constexpr int RIGHT_STICK_X = 5; 
    constexpr int RIGHT_STICK_Y = 4;

    constexpr int LAUNCHPAD_CONTROLLER_PORT = 1;
}