// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>
#include "subsystems/DriveTrain.h"
#include "subsystems/Launcher.h"
#include "subsystems/Intake.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoDrive
    : public frc2::CommandHelper<frc2::ParallelCommandGroup, AutoDrive> {

 public:
  explicit AutoDrive(DriveTrain *drivetrain, Launcher *launcher);
 
 private:
   DriveTrain *m_driveTrain;

};
