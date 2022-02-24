// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Test.h"
#include "subsystems/ExampleSubsystem.h"

Test::Test(ExampleSubsystem *example, int direction) : m_example{example}, m_direction{direction} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(example);
}

// Called when the command is initially scheduled.
void Test::Initialize() {
  m_example->TestRelay(m_direction);
  m_example->TestServo(m_direction);
}

// Called repeatedly when this Command is scheduled to run
void Test::Execute() {}

// Called once the command ends or is interrupted.
void Test::End(bool interrupted) {}

// Returns true when the command should end.
bool Test::IsFinished() {
  return true;
}
