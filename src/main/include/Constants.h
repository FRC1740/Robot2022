/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//On error, create env.h from env-default.h and modify ROBOT_VERSION_STRING
#include "env.h"

#include <cmath>  // for std::fabs
#include <math.h>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace ConMath {
    constexpr double PI = M_PI; // 3.141592;
    constexpr double METERS_2_INCH = .0254; // m/in
    constexpr double MINUTES_2_SECONDS = 1/60.; // sec/min
    constexpr double RAD_2_DEG = 180.0/PI;
    constexpr double DEG_2_RAD = 1/RAD_2_DEG;
}

namespace ConLimelight {
    constexpr int VISION_MODE = 0;
    constexpr int CAMERA_MODE = 1;

    constexpr int LED_PIPLINE_DEFAULT = 0;
    constexpr int LED_OFF = 1;
    constexpr int LED_BLINK = 2;
    constexpr int LED_ON = 3;

    constexpr int SNAPSHOT_STOP = 0;
    constexpr int SNAPSHOT_START = 1;

    constexpr double HORIZONTAL_TOLERANCE = 1.0;  //degrees
    constexpr double TARGET_HEIGHT = 38.5; //in to center of target
    constexpr double CAMERA_HEIGHT = 19.5; //in to center of camera
    constexpr double MAX_HORIZONTAL_OFFSET = 29.8; //degrees

    // constexpr cv::Matx33d cameraMatrix = cv::Matx33d(
    //                     772.53876202, 0., 479.132337442,
    //                     0., 769.052151477, 359.143001808,
    //                     0., 0., 1.0);
    // constexpr std::vector istortionCoefficient =  std::vector<double> {
    //                     2.9684613693070039e-01, -1.4380252254747885e+00,-2.2098421479494509e-03,
    //                     -3.3894563533907176e-03, 2.5344430354806740e+00};

    constexpr double focalLength = 2.9272781257541; //mm
}

namespace ConNEO {
    constexpr int MAXIMUM_RPM = 5676;
    constexpr int GEAR_RATIO = 10.71;
}

namespace ConShuffleboard {
    constexpr char RobotTab[] = "Robot";
    constexpr char ClimberTab[] = "Climber";
    constexpr char ControlPanelManipulatorTab[] = "CPM";
    constexpr char DriveTrainTab[] = "DriveTrain";
    constexpr char ShooterTab[] = "Shooter";
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