// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Intake.h"

Intake::Intake()
    : PIDSubsystem(
        // The PIDController used by the subsystem
        frc2::PIDController(0, 0, 0)) {
        // Initialize the DoubleSolenoid so it knows where to start.  Not required for single solenoids.
        deployDoublePCM.Set(frc::DoubleSolenoid::Value::kReverse);
        }

void Intake::Deploy() {
  deployDoublePCM.Set(frc::DoubleSolenoid::Value::kForward);

}

void Intake::Retract() {
  deployDoublePCM.Set(frc::DoubleSolenoid::Value::kReverse);
}

void Intake::UseOutput(double output, double setpoint) {
  // Use the output here
}

double Intake::GetMeasurement() {
  // Return the process variable measurement here
  return 0;
}
