// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDriveDistance.h"
#include <frc/smartdashboard/SmartDashboard.h>

AutoDriveDistance::AutoDriveDistance(DriveTrain *drivetrain, double distance) : m_driveTrain(drivetrain), m_distance(distance){
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
}

// Called when the command is initially scheduled.
void AutoDriveDistance::Initialize() {
  m_driveTrain->m_nte_Testing.SetDouble(m_driveTrain->GetLeftDistance());
  m_driveTrain->ResetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveDistance::Execute() {
  // See TeleOpDrive for more filtering information
  constexpr double speedN = 11.0; // length of digital filter
  constexpr double maxSpeed = 0.5;
  constexpr double rotation = 0.0;

  double desiredSpeed = (m_distance > m_driveTrain->GetAverageEncoderDistance()) ? -maxSpeed : maxSpeed;
  double speed = (((speedN - 1.0) * m_speedOut) + desiredSpeed) / speedN;
  m_driveTrain->ArcadeDrive(speed, rotation);
  m_speedOut = speed;
}

// Called once the command ends or is interrupted.
void AutoDriveDistance::End(bool interrupted) {
  m_driveTrain->ArcadeDrive(0.0, 0.0);
  printf("AutoDriveDistance::End()\n");
}

// Returns true when the command should end.
bool AutoDriveDistance::IsFinished() {
  constexpr double epsilon = 5.0;
  frc::SmartDashboard::PutNumber("Drive Distance: ", m_driveTrain->GetAverageEncoderDistance());

  return ((fabs(m_distance + copysign(epsilon / 2.0, m_distance))- m_driveTrain->GetAverageEncoderDistance()) < epsilon);
}
