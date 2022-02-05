// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Retract.h"

Retract::Retract(Intake *intake) : m_intake{intake} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(intake);
}

// Called when the command is initially scheduled.
void Retract::Initialize() {
  m_intake->Retract();
}

// Called repeatedly when this Command is scheduled to run
void Retract::Execute() {}

// Called once the command ends or is interrupted.
void Retract::End(bool interrupted) {}

// Returns true when the command should end.
bool Retract::IsFinished() {
  return true;
}
