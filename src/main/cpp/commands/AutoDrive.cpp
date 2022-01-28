// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDrive.h"
#include "commands/AutoDriveDistance.h"
#include "commands/AutoDelay.h"
#include "commands/AutoTurn.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>

/*
  Basic Autonomous Testing
  (1) Delay a seconds
  (2) drive backwards for b seconds
  (3) Turn to c angle
*/

AutoDrive::AutoDrive(DriveTrain *drivetrain, Launcher *launcher) : m_driveTrain(drivetrain) {
#if defined(ENABLE_DRIVETRAIN)
  // SHuffleboard parameters NOT refreshing this way. Moving them into the specific commands instead of
  // passing them as arguments to the command seems to function as desired.
  // units::time::second_t a = .5_s; // FIXME: Temporary pending proper type conversion double -> second_t
  // double a = m_driveTrain->m_nte_a_DriveDelay.GetDouble(0.0); // Drive delay (seconds)
  // double c = m_driveTrain->m_nte_c_DriveTurnAngle.GetDouble(0.0); // Turning Angle (degrees)

  #if !defined(ENABLE_LAUNCHER)
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands (
    frc2::SequentialCommandGroup { AutoDelay(drivetrain), AutoDriveDistance(drivetrain), AutoTurn(drivetrain) }
    ); /* */
  #endif
  #if defined(ENABLE_LAUNCHER)
  // Add autonomous drive & launcher commands
  AddCommands (
    frc2::SequentialCommandGroup{ AutoDelay(a), 
                                  frc2::ParallelRaceGroup{ AutoDriveDistance(drivetrain, b), AutoDelay(5.0) }
                                },
    frc2::ParallelRaceGroup{ LaunchBall(launcher), AutoDelay(c) },
    frc2::SequentialCommandGroup{ AutoDelay(d),
                                  frc2::ParallelRaceGroup{ IntakeBall(intake), AutoDelay(e) }
                                }
  );
  #endif  // defined(ENABLE_LAUNCHER)
#endif // defined(ENABLE_DRIVETRAIN)
}
