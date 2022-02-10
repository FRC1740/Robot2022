// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Launcher.h"
#include "OI.h"

Launcher::Launcher()
    : PIDSubsystem(
          // The PIDController used by the subsystem
          frc2::PIDController(0, 0, 0)) {
            // Initialize stuff here
            #ifdef ENABLE_LAUNCHER
            // Enable & Set Encoder Soft Limits...
            m_launcherMotorBert.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
            m_launcherMotorBert.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
            m_launcherMotorErnie.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
            m_launcherMotorErnie.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
            // Forward Limits
            m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Bert_FwdLimit.GetDouble(ConLauncher::BERT_FWD_LIMIT));
            m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, m_nte_Bert_RevLimit.GetDouble(ConLauncher::BERT_REV_LIMIT));
            m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Ernie_FwdLimit.GetDouble(ConLauncher::ERNIE_FWD_LIMIT));
            m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, m_nte_Ernie_RevLimit.GetDouble(ConLauncher::ERNIE_REV_LIMIT));

            // Naturally, Bert is Backwards...
            m_launcherMotorBert.SetInverted(true);
            m_launcherMotorErnie.SetInverted(false);

            // Set Current limits (Stall, Free)
            m_launcherMotorBert.SetSmartCurrentLimit(ConLauncher::CURRENT_STALL_LIMIT, ConLauncher::CURRENT_STALL_LIMIT);
            m_launcherMotorErnie.SetSmartCurrentLimit(ConLauncher::CURRENT_STALL_LIMIT, ConLauncher::CURRENT_STALL_LIMIT);

            // Save the configuration to flash memory
            m_launcherMotorErnie.BurnFlash();
            m_launcherMotorBert.BurnFlash();

            m_sbt_Launcher = &frc::Shuffleboard::GetTab(ConShuffleboard::LauncherTab);

            m_nte_Ernie_FwdLimit = m_sbt_Launcher->AddPersistent("Ernie Limit", ConLauncher::ERNIE_FWD_LIMIT)
                  .WithSize(2,1)
                  .WithPosition(0,0)
                  .GetEntry();
            m_nte_Bert_FwdLimit = m_sbt_Launcher->AddPersistent("Bert Limit", ConLauncher::BERT_FWD_LIMIT)
                  .WithSize(2,1)
                  .WithPosition(0,1)
                  .GetEntry();
            #endif            
          }

void Launcher::Launch() {
  LaunchBert();
  LaunchErnie();
}

void Launcher::LaunchBert() {
  // Launch a ball
  m_launcherMotorBert.Set(1.0);
}

void Launcher::LaunchErnie() {
  // Launch a ball
  m_launcherMotorErnie.Set(1.0);
}

void Launcher::Retract() {
  // Bring both launchers back
  RetractBert();
  RetractErnie();
}

void Launcher::RetractBert() {
  m_launcherMotorBert.Set(-.10);
}

void Launcher::RetractErnie() {
  m_launcherMotorErnie.Set(-.10);
}
void Launcher::SetLaunchSoftLimit() {
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Ernie_FwdLimit.GetDouble(115.0));
  // WARNING: May need to use kReverse for Bert...
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Bert_FwdLimit.GetDouble(115.0));
}

void Launcher::SetResetSoftLimit() {}

void Launcher::Reset() {}

void Launcher::UseOutput(double output, double setpoint) {
  // Use the output here
}

double Launcher::GetMeasurement() {
  // Return the process variable measurement here
  return 0;
}

void Periodic() {
  // Push/Pull stuff from the Network Tables
}