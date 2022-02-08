// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Climb.h"

namespace ConClimber {
  constexpr double MOTOR_ID = 8.0;
  constexpr double MOTOR_SPEED = 1.0;
}

Climb::Climb(Climber *climber) : m_climber{climber} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(climber);
}

// Called when the command is initially scheduled.
void Climb::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {
  m_climber->Climb();
}

// Called once the command ends or is interrupted.
void Climb::End(bool interrupted) {
  m_climber->Stop();
}

// Returns true when the command should end.
bool Climb::IsFinished() {
  return false;
}
