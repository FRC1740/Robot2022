// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrain.h"

// Moved to DriveTrain.h
// namespace ConAutoDriveDistance {
//   constexpr double DISTANCE = 86; // Inches (negative is reverse) Needed to exit the 
//   constexpr double LAUNCH_DELAY = 0.5; // Seconds to delay between launch & drive
// }

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoDriveDistance
    : public frc2::CommandHelper<frc2::CommandBase, AutoDriveDistance> {
 public:
  AutoDriveDistance(DriveTrain *drivetrain, double distance);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  DriveTrain *m_driveTrain;
  double m_distance_inches = 0.0; // CRE 2022-01-28 Read from shuffleboard
  double m_speedOut = 0.0;
};
