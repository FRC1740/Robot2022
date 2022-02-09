// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDrive.h"
#include "commands/AutoDriveDistance.h"
#include "commands/AutoDelay.h"
#include "commands/AutoTurn.h"
#include "commands/Deploy.h"
#include "commands/Stow.h"
#include "commands/Launch.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>

/*
  Basic Autonomous Testing
  (1) Delay a seconds
  (2) drive backwards for b seconds
  (3) Turn to c angle
*/

AutoDrive::AutoDrive(DriveTrain *drivetrain, Launcher *launcher, Intake *intake) : m_driveTrain(drivetrain) {
#if defined(ENABLE_DRIVETRAIN)
  // SHuffleboard parameters NOT refreshing this way. Moving them into the specific commands instead of
  // passing them as arguments to the command seems to function as desired.
  // units::time::second_t a = .5_s; // FIXME: Temporary pending proper type conversion double -> second_t
  // double a = m_driveTrain->m_nte_a_DriveDelay.GetDouble(0.0); // Drive delay (seconds)
  // double c = m_driveTrain->m_nte_c_DriveTurnAngle.GetDouble(0.0); // Turning Angle (degrees)

  #if !defined(FOO)
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands (
    frc2::SequentialCommandGroup {  AutoDelay(1.5_s), 
                                    AutoDriveDistance(drivetrain),
                                    AutoTurn(drivetrain),
                                    Launch(launcher),
                                    Deploy(intake)
                                 } );
  #endif
  #if 0
  // Add autonomous drive & launcher commands
  AddCommands (
    frc2::SequentialCommandGroup { AutoDelay(1.5_s), AutoDriveDistance(drivetrain), AutoTurn(drivetrain) },
    frc2::SequentialCommandGroup{ AutoDelay(1.0_s), 
                                  frc2::ParallelRaceGroup{ Deploy(intake), AutoDelay(1.0_s) }
                                }
    /*
    frc2::ParallelRaceGroup{ Launch(launcher), AutoDelay() },
    frc2::SequentialCommandGroup{ AutoDelay(1.0_s),
                                  frc2::ParallelRaceGroup{ Deploy(intake), AutoDelay(1.0_s) }
                                }
    */
  );
  #endif  // defined(ENABLE_LAUNCHER)
#endif // defined(ENABLE_DRIVETRAIN)
}
