// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
// #include <frc2/command/PIDCommand.h> // if need PIDCommand, use this instead of CommandHelper
#include "subsystems/Launcher.h"

class Launch
    : public frc2::CommandHelper<frc2::CommandBase, Launch> {      
    // : public frc2::CommandHelper<frc2::PIDCommand, Launch> { // if need PIDCommand, use this
 public:
  Launch(Launcher *);
  void Initialize();
  void Execute();
  void End();
  bool IsFinished() override;

 private:
  Launcher *m_launcher;
};
