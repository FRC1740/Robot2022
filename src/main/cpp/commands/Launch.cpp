// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Launch.h"

Launch::Launch(Launcher *launcher) : m_launcher{launcher} {
  AddRequirements(launcher);
}

// PID Command does not use these three methods...
void Launch::Initialize() {
  printf("Launch Command: Launching!\n");
  m_launcher->Launch();
}

void Launch::Execute() {}

void Launch::End() {
  printf("Launch Command: Retracting launcher\n");
  m_launcher->Retract();
}

// Returns true when the command should end.
bool Launch::IsFinished() {
  return true;
}
