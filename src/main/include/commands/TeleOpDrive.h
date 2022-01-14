/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrain.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */

class TeleOpDrive
    : public frc2::CommandHelper<frc2::CommandBase, TeleOpDrive> {
 public:
  explicit TeleOpDrive(DriveTrain *drivetrain,
                       std::function<double()> speed,
                       std::function<double()> rotation);

#ifdef ENABLE_DRIVETRAIN
  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
#endif // ENABLE_DRIVETRAIN

 private:
  DriveTrain *m_driveTrain;
  std::function<double()> m_speed;
  std::function<double()> m_rotation;
  // Digital filter outputs
  double m_speedOut = 0.0;
  double m_rotationOut = 0.0;
};
