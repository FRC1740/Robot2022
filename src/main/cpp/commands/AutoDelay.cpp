// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDelay.h"

AutoDelay::AutoDelay(units::time::second_t seconds) : m_seconds(seconds) {
  // Use addRequirements() here to declare subsystem dependencies.
  m_timer = frc::Timer(); 
}

// Called when the command is initially scheduled.
void AutoDelay::Initialize() {
  m_timer.Reset();
  m_timer.Start();
  // m_seconds = (units::time::second_t)m_driveTrain->m_nte_a_DriveDelay.GetDouble(0.0); // Seconds delay before driving
  #ifdef DEBUG && DEBUG == TRUE
    printf("AutoDelay()::Initialize()\n");
  #endif
}   

// Called repeatedly when this Command is scheduled to run
// void AutoDelay::Execute() {}

// Called once the command ends or is interrupted.
void AutoDelay::End(bool interrupted) {
  #ifdef DEBUG
    printf("AutoDelay::End()\n");
  #endif
}

// Returns true when the command should end.
bool AutoDelay::IsFinished() {
  // m_timer.Get() returns a units::time::second_t
  return m_timer.Get() > m_seconds;
}
