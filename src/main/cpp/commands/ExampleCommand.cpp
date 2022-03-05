// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/SelectCommand.h>
#include "commands/ExampleCommand.h"

ExampleCommand::ExampleCommand(ExampleSubsystem* subsystem)
    : m_subsystem{subsystem} {

  // The robot's subsystems and commands are defined here...

  // An example selectcommand.  Will select from the three commands based on the
  // value returned by the selector method at runtime.  Note that selectcommand
  // takes a generic type, so the selector does not have to be an enum; it could
  // be any desired type (string, integer, boolean, double...)
  frc2::SelectCommand<CommandSelector> m_exampleSelectCommand{
      [this] { return Select(); },
      // Maps selector values to commands
      std::pair{ONE, frc2::PrintCommand{"Command one was selected!"}},
      std::pair{TWO, frc2::PrintCommand{"Command two was selected!"}},
      std::pair{THREE, frc2::PrintCommand{"Command three was selected!"}}};


}