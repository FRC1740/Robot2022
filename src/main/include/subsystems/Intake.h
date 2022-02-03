// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/DoubleSolenoid.h>
#include <frc/XboxController.h>
#include "Robot.h"

class Intake : public frc2::PIDSubsystem {
 public:
  Intake();
  void Deploy();
  void Retract();

 protected:
  void UseOutput(double output, double setpoint) override;

  double GetMeasurement() override;

  frc::DoubleSolenoid deployDoublePCM{frc::PneumaticsModuleType::CTREPCM, 1, 2};
};
