// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Shooter.h"

Shooter::Shooter()
    : PIDSubsystem(
          // The PIDController used by the subsystem
          frc2::PIDController(0, 0, 0)) {}

void Shooter::UseOutput(double output, double setpoint) {
  // Use the output here
}

double Shooter::GetMeasurement() {
  // Return the process variable measurement here
  return 0;
}
