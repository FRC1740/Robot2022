// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Reject.h"

Reject::Reject(Intake *intake) : m_intake{intake} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(intake);
}

// Called when the command is initially scheduled.
void Reject::Initialize() {
  m_intake->Reject();
}

// Called repeatedly when this Command is scheduled to run
void Reject::Execute() {}

// Called once the command ends or is interrupted.
void Reject::End(bool interrupted) {
  m_intake->Load();
}

// Returns true when the command should end.
bool Reject::IsFinished() {
  return false;
}
