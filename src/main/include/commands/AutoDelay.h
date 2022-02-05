// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include "subsystems/DriveTrain.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoDelay
    : public frc2::CommandHelper<frc2::CommandBase, AutoDelay> {
 public:
  explicit AutoDelay(units::time::second_t);

  void Initialize() override;

  // void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  DriveTrain *m_driveTrain;
  units::time::second_t m_seconds;
  // double m_seconds; // Don't know how to type convert the NTE GetDouble() -> second_t
  frc::Timer m_timer;  
};
