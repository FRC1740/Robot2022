// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Test.h"
#include "subsystems/Intake.h"

Test::Test(Intake *intake, int direction) : m_intake{intake}, m_direction{direction} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(intake);
}

// Called when the command is initially scheduled.
void Test::Initialize() {
  // m_intake->TestRelay(m_direction);
  m_intake->TestServo(m_direction);
}

// Called repeatedly when this Command is scheduled to run
void Test::Execute() {
}

// Called once the command ends or is interrupted.
void Test::End(bool interrupted) {}

// Returns true when the command should end.
bool Test::IsFinished() {
  return false;
}
