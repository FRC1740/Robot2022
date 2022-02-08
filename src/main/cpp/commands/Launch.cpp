// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Launch.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html

/* May not need to be a PID Command...
Launch::Launch()
    : CommandHelper(
          frc2::PIDController(0, 0, 0),
          // This should return the measurement
          [] { return 0; },
          // This should return the setpoint (can also be a constant)
          [] { return 0; },
          // This uses the output
          [](double output) {
            // Use the output here
          }) {}

/* */

Launch::Launch(Launcher *launcher) : m_launcher{launcher} {
  AddRequirements(launcher);
}

// PID Command does not use these three methods...
void Launch::Initialize() {
    m_launcher->Launch();
}
void Launch::Execute() {
}
void Launch::End() {
  m_launcher->Retract();
}

// Returns true when the command should end.
bool Launch::IsFinished() {
  return false;
}
