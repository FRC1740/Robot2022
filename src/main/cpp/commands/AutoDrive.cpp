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
#include <frc2/command/InstantCommand.h>
#include <frc2/command/StartEndCommand.h>

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

  double m_distance = m_driveTrain->m_autoDistance;
  int m_mode = m_driveTrain->m_autoDriveMode;
  // Remove the following to allow any mode
  m_mode = ConDriveTrain::AUTONOMOUS_MODE_SHOOT_DELAY_MOVE;
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  switch (m_mode) {
    case ConDriveTrain::AUTONOMOUS_MODE_SHOOT_DELAY_MOVE:
      AddCommands (
        frc2::SequentialCommandGroup {
            frc2::InstantCommand( [launcher] { launcher->LaunchBert(); }, { launcher }),
            frc2::InstantCommand( [launcher] { launcher->LaunchErnie(); }, { launcher }),
    //        Launch(launcher),
            AutoDelay(0.5_s),
            frc2::InstantCommand( [launcher] { launcher->RetractBert(); }, { launcher }),
            frc2::InstantCommand( [launcher] { launcher->RetractErnie(); }, { launcher }),
            frc2::InstantCommand( [intake] { intake->Deploy(); }, { intake }),
            AutoDriveDistance(drivetrain, m_distance),
            frc2::InstantCommand( [intake] { intake->Stow(); }, {intake}),
            AutoDelay(0.5_s),
            AutoDriveDistance(drivetrain, -m_distance),
            AutoDelay(0.25_s),
            frc2::InstantCommand( [launcher] { launcher->LaunchBert(); }, { launcher }),
            frc2::InstantCommand( [launcher] { launcher->LaunchErnie(); }, { launcher }),                                  
            AutoDelay(0.5_s),
            frc2::InstantCommand( [launcher] { launcher->RetractBert(); }, { launcher }),
            frc2::InstantCommand( [launcher] { launcher->RetractErnie(); }, { launcher }),
          } );
    break;

    case ConDriveTrain::AUTONOMOUS_MODE_JUST_MOVE:
    break;

    case ConDriveTrain::AUTONOMOUS_MODE_5_BALL:
    break;
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

  } // switch(mode)
#endif // defined(ENABLE_DRIVETRAIN)
}
