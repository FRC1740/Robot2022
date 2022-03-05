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
#include <frc2/command/SelectCommand.h>

AutoDrive::AutoDrive(DriveTrain *drivetrain, Launcher *launcher, Intake *intake) {
  m_driveTrain = drivetrain;
  m_launcher = launcher;
  m_intake = intake;

  #if defined(ENABLE_DRIVETRAIN)
    // SHuffleboard parameters NOT refreshing this way. Moving them into the specific commands instead of
    // passing them as arguments to the command seems to function as desired.
    // units::time::second_t a = .5_s; // FIXME: Temporary pending proper type conversion double -> second_t
    // double a = drivetrain->m_nte_a_DriveDelay.GetDouble(0.0); // Drive delay (seconds)
    // double c = drivetrain->m_nte_c_DriveTurnAngle.GetDouble(0.0); // Turning Angle (degrees)

  // An example selectcommand.  Will select from the three commands based on the
    // value returned by the selector method at runtime.  Note that selectcommand
    // takes a generic type, so the selector does not have to be an enum; it could
    // be any desired type (string, integer, boolean, double...)

    #if 0
    frc2::SelectCommand<CommandSelector> m_exampleSelectCommand{
        [this] { return Select(); },
        // Maps selector values to commands
        std::pair{ONE, frc2::SequentialCommandGroup {
                        frc2::PrintCommand{"Command one was selected!"},
                        AutoDriveDistance(drivetrain, m_distance),
                        }  },
        std::pair{TWO, frc2::PrintCommand{"Command two was selected!"}
                },
        std::pair{THREE, frc2::PrintCommand{"Command three was selected!"}
                }
        };
    #endif
    #if 1
    // Should be set in AutonomousInit() as well as DisabledPeriodic()
    //m_driveTrain->SetAutonomousParameters();

    double m_distance = m_driveTrain->m_autoDistance;
    int m_mode = static_cast <int>(m_driveTrain->m_autoDriveMode+.5);
    printf("m_mode: %d, m_autoDriveMode: %f\n", m_mode, m_driveTrain->m_autoDriveMode);
    printf("Driving distance: %f\n", m_distance);
    printf("Drive delay: %f\n", m_driveTrain->m_autoDriveDelay);

    // Uncomment one of the following to force a specific Autonomous mode 
    // m_mode = ConDriveTrain::AUTONOMOUS_MODE_2_BALL;
    // m_mode = ConDriveTrain::AUTONOMOUS_MODE_LAUNCH_DELAY_MOVE;

    // Add your commands here, e.g.
    // AddCommands(FooCommand(), BarCommand());
    switch (m_mode) {
      case ConDriveTrain::AUTONOMOUS_MODE_2_BALL:
        printf("Autonomous %d Ball Mode", m_mode);
        AddCommands (
          frc2::SequentialCommandGroup { 
              frc2::InstantCommand( [intake] { intake->Deploy(); }, { intake }), 
              AutoDelay(0.5), 
              frc2::InstantCommand( [&] { m_launcher->LaunchBert(); }, { m_launcher }),
              frc2::InstantCommand( [&] { m_launcher->LaunchErnie(); }, { m_launcher }),
              AutoDelay(0.5),
              frc2::InstantCommand( [&] { m_launcher->RetractBert(); }, { m_launcher }),
              frc2::InstantCommand( [&] { m_launcher->RetractErnie(); }, { m_launcher }),
              AutoDriveDistance(m_driveTrain, 84.0),
              frc2::InstantCommand( [intake] { intake->Stow(); }, {intake}),
              AutoDelay(0.5), 
              AutoDriveDistance(m_driveTrain, -84.0),
              frc2::InstantCommand( [intake] { intake->Deploy(); }, { intake }), 
              AutoDelay(0.5),
              frc2::InstantCommand( [&] { m_launcher->LaunchBert(); }, { m_launcher }),
              frc2::InstantCommand( [&] { m_launcher->LaunchErnie(); }, { m_launcher }),                                  
              AutoDelay(0.5),
              frc2::InstantCommand( [intake] { intake->Stow(); }, {intake}),
              frc2::InstantCommand( [&] { m_launcher->RetractBert(); }, { m_launcher }),
              frc2::InstantCommand( [&] { m_launcher->RetractErnie(); }, { m_launcher }),
              #if 0
              // possible additional ball pickup?
              AutoTurn(m_driveTrain, 45.0),
              AutoDelay(0.5),
              AutoDriveDistance(m_driveTrain, 84.0),
              #endif
            } );
      break;

      case ConDriveTrain::AUTONOMOUS_MODE_LAUNCH_DELAY_MOVE:
        printf("Autonomous Mode %d: Shoot-Delay-Move", m_mode);
        AddCommands (
            frc2::SequentialCommandGroup {
              frc2::InstantCommand( [&] { m_launcher->LaunchBert(); }, { m_launcher }),
              frc2::InstantCommand( [&] { m_launcher->LaunchErnie(); }, { m_launcher }),
              AutoDelay(m_driveTrain->m_autoDriveDelay),
              frc2::InstantCommand( [&] { m_launcher->RetractBert(); }, { m_launcher }),
              frc2::InstantCommand( [&] { m_launcher->RetractErnie(); }, { m_launcher }),
              AutoDriveDistance(m_driveTrain, m_distance),
          } );
      break;

      case ConDriveTrain::AUTONOMOUS_MODE_5_BALL:
      break;
    
    #if 0
    // Add autonomous drive & launcher commands
    AddCommands (
      frc2::SequentialCommandGroup { AutoDelay(1.5_s), AutoDriveDistance(m_driveTrain), AutoTurn(m_driveTrain) },
      frc2::SequentialCommandGroup{ AutoDelay(1.0_s), 
                                    frc2::ParallelRaceGroup{ Deploy(intake), AutoDelay(1.0_s) }
                                  }
      /*
      frc2::ParallelRaceGroup{ Launch(m_launcher), AutoDelay() },
      frc2::SequentialCommandGroup{ AutoDelay(1.0_s),
                                    frc2::ParallelRaceGroup{ Deploy(intake), AutoDelay(1.0_s) }
                                  }
      */
    );
    #endif  // defined(ENABLE_LAUNCHER)

    } // switch(mode)
    #endif // if 0
  #endif // defined(ENABLE_DRIVETRAIN)

}