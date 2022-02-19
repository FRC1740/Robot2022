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
    constexpr int ON = 3;
    constexpr int BLINK = 2;
    constexpr int OFF = 1;
}

class Vision : public frc2::SubsystemBase {
 public:
  Vision();

#ifdef ENABLE_VISION
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  double Align();

  void ToggleLight();

  void LightOn();

  void LightOff();

  void SelectPlayerStationPipeline();

  void SelectNearGoalPipeline();

  void SelectFarGoalPipeline();

#endif // ENABLE_VISION

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  std::shared_ptr<nt::NetworkTable> m_nt_Limelight;

 public:
  frc::ShuffleboardTab *m_sbt_Vision;
  nt::NetworkTableEntry m_nte_Align_P;
  nt::NetworkTableEntry m_nte_Align_I;
  nt::NetworkTableEntry m_nte_Align_D;

  double m_nte_tx;
};
