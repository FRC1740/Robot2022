/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "Constants.h"
#include <frc2/command/SubsystemBase.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>

namespace ConVision {
    namespace AlignToPlayerStation {
        constexpr double P = 0.15;
        constexpr double I = 0.0;
        constexpr double D = 0.0;
    }
    // LED Modes: Write to NT "ledMode"
    constexpr int ON = 3; 
    constexpr int BLINK = 2;
    constexpr int OFF = 1;

    // Pipelines: 0 = Vision Processing; 1 = Driver
    constexpr int VISION_PIPELINE = 0;
    constexpr int DRIVER_PIPELINE = 1;
    
    // Stream: 1 = Primary only; 2 = Primary/2nd PIP; 3 = 2nd/Primary PIP
    constexpr int PRIMARY_ONLY = 1;
    constexpr int PRIMARY_SECONDARY_PIP = 2;
    constexpr int SECONDARY_PRIMARY_PIP = 3;

    // Camera Mode: Write to NT "camMode"
    constexpr int DRIVER_ONLY = 1;
    constexpr int VISION_TRACKING = 0;
}

class Vision : public frc2::SubsystemBase {
 public:
  Vision();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void InitVision();

#ifdef ENABLE_VISION
  void Periodic();
  double Align();
  void ToggleLight();
  void LightOn();
  void LightOff();
  void LightBlink();
  void PrimaryStream();
  void PiPStream();

  void SelectPlayerStationPipeline();
  void SelectNearGoalPipeline();
  void SelectFarGoalPipeline();

#endif // ENABLE_VISION

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  std::shared_ptr<nt::NetworkTable> m_nt_Limelight;
  int m_LEDStatus;
  int m_Stream;

 public:
  frc::ShuffleboardTab *m_sbt_Vision;
  nt::NetworkTableEntry m_nte_Align_P;
  nt::NetworkTableEntry m_nte_Align_I;
  nt::NetworkTableEntry m_nte_Align_D;

  double m_nte_tx;
};
