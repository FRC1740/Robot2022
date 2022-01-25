// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDrive.h"
#include "commands/AutoDriveDistance.h"
#include "commands/AutoDelay.h"
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
#if defined(ENABLE_DRIVETRAIN) && defined(ENABLE_LAUNCHER)
  units::time::second_t a = .5_s; // FIXME: Temporary pending proper type conversion double -> second_t
  // double a = m_driveTrain->m_nte_a_DriveDelay.GetDouble(0.0); // Drive delay (seconds)
  double b = m_driveTrain->m_nte_b_DriveDistance.GetDouble(0.0); // Drive distance (inches)
  double c = m_driveTrain->m_nte_c_DriveTurnAngle.GetDouble(0.0); // Turning Angle

  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands (
    frc2::SequentialCommandGroup { AutoDelay(a), AutoDriveDistance(drivetrain, b) }
    ); /* */

  #if 0
  // Need to define each of the commands below
  AddCommands (
    frc2::SequentialCommandGroup{ AutoDelay(a), 
                                  frc2::ParallelRaceGroup{ AutoDriveDistance(drivetrain, b), AutoDelay(5.0) }
                                },
    frc2::ParallelRaceGroup{ SpinUpShooter(shooter), AutoDelay(c) },
    frc2::SequentialCommandGroup{ AutoDelay(d),
                                  frc2::ParallelRaceGroup{ JumbleShooter(shooter, -1), AutoDelay(e) }
                                }
  );
  #endif
#endif // defined(ENABLE_DRIVETRAIN) && defined(ENABLE_SHOOTER)
}
