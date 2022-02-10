/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <cmath>  // for std::fabs
#include <math.h>

//On error, create env.h from env-default.h and modify ROBOT_VERSION_STRING
#include "env.h"

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

namespace ConSparkMax {
    constexpr double POSITION_CONVERSION_FACTOR = 42.0;
}
