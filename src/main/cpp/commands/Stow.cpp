// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Stow.h"

Stow::Stow(Intake *intake) : m_intake{intake} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(intake);
}

// Called when the command is initially scheduled.
void Stow::Initialize() {
  m_intake->Stow();
}

// Called repeatedly when this Command is scheduled to run
void Stow::Execute() {}

// Called once the command ends or is interrupted.
void Stow::End(bool interrupted) {}

// Returns true when the command should end.
bool Stow::IsFinished() {
  return true;
}
