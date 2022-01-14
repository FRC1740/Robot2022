/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TeleOpDrive.h"
#include <frc/smartdashboard/SmartDashboard.h>

TeleOpDrive::TeleOpDrive(DriveTrain *drivetrain,
                         std::function<double()> speed,
                         std::function<double()> rotation)
            : m_driveTrain(drivetrain),
              m_speed(speed),
              m_rotation(rotation) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
}

#ifdef ENABLE_DRIVETRAIN
// Called when the command is initially scheduled.
void TeleOpDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TeleOpDrive::Execute() {
  // Digital filter lengths- between 1.0 (no filter) and 20.0 (90% at 1 second) (11.0 is 90% at 0.5 sec)
  // Idea from simple filter at https://www.chiefdelphi.com/t/moderating-acceleration-deceleration/77960/4

  // Get adjustment values
  double speedN = m_driveTrain->m_nte_DriveSpeedFilter.GetDouble(10.0);
  double rotationN = m_driveTrain->m_nte_DriveRotationFilter.GetDouble(8.0);
  if (speedN < 1.0) { speedN = 1.0; }
  if (rotationN < 1.0) { rotationN = 1.0; }
  double exponent = m_driveTrain->m_nte_InputExponent.GetDouble(1.0);
  if (exponent < 1.0) { exponent = 1.0; }
  if (exponent > 3.0) { exponent = 3.0; }

  // Adjust input speed with exponentiation
  double speed = m_speed();
  double adjustedSpeed = copysign(pow(fabs(speed), exponent), speed);

  // Adjust input speed and input rotation with filters
  speed = (((speedN - 1.0) * m_speedOut) + adjustedSpeed) / speedN;
  double rotation = (((rotationN - 1.0) * m_rotationOut) + m_rotation()) / rotationN;

  // Do it
  m_driveTrain->ArcadeDrive(speed, rotation);

  m_speedOut = speed;
  m_rotationOut = rotation;

  // Options for more accurate time:
  //frc::RobotController::GetFPGATime()/1000
  // For Linear Filters:
  // From https://docs.wpilib.org/en/latest/docs/software/advanced-control/filters/linear-filter.html#creating-a-linearfilter
  //frc::LinearFilter<double> filter = frc::LinearFilter<double>::SinglePoleIIR(0.1_s, 0.02_s);
}

// Called once the command ends or is interrupted.
void TeleOpDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool TeleOpDrive::IsFinished() { return false; }

#endif // ENABLE_DRIVETRAIN
