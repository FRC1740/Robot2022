// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoTurn.h"

AutoTurn::AutoTurn(DriveTrain *drivetrain) : m_driveTrain(drivetrain) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AutoTurn::Initialize() {
  m_driveTrain->ResetGyro();
  // Read the target angle from the dashboard
  m_angle_degrees = m_driveTrain->m_nte_b_DriveDistance.GetDouble(0.0);
}

// Called repeatedly when this Command is scheduled to run
void AutoTurn::Execute() {
  // See TeleOpDrive for more filtering information
  constexpr double rotationN = 11.0; // length of digital filter *** We should read this from Network Tables
  constexpr double maxRotation = 0.5;
  constexpr double speed = 0.0;

  double desiredRotation = (m_angle_degrees < m_driveTrain->GetGyroAngle()) ? maxRotation : -maxRotation;
  double rotation = (((rotationN - 1.0) * m_rotationOut) + desiredRotation) / rotationN;
  m_driveTrain->ArcadeDrive(speed, rotation);
  m_rotationOut = rotation;  
}

// Called once the command ends or is interrupted.
void AutoTurn::End(bool interrupted) {
  m_driveTrain->ArcadeDrive(0.0, 0.0);  
}

// Returns true when the command should end.
bool AutoTurn::IsFinished() {
  return false;
}
