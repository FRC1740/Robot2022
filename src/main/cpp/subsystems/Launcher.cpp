// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Launcher.h"

Launcher::Launcher()
    : PIDSubsystem(
          // The PIDController used by the subsystem
          frc2::PIDController(0, 0, 0)) {
            // Initialize stuff here
            m_launcherMotor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
            m_launcherMotor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
          }

void Launcher::Launch() {
  // Launch a ball
}

void Launcher::SetLaunchSoftLimit() {

}

void Launcher::SetResetSoftLimit() {

}

void Launcher::Reset() {

}

void Launcher::UseOutput(double output, double setpoint) {
  // Use the output here
}

double Launcher::GetMeasurement() {
  // Return the process variable measurement here
  return 0;
}
