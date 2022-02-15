// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/SubsystemBase.h>
#include "subsystems/Launcher.h"
#include "OI.h"

Launcher::Launcher() {
            // Initialize stuff here
            #ifdef ENABLE_LAUNCHER
            m_launcherEncoderBert.SetPosition(0.0);
            m_launcherEncoderErnie.SetPosition(0.0);
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
            #endif            

            m_sbt_Launcher = &frc::Shuffleboard::GetTab(ConShuffleboard::LauncherTab);

            m_nte_Ernie_FwdLimit = m_sbt_Launcher->AddPersistent("Ernie Fwd Limit", ConLauncher::ERNIE_FWD_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(0,0)
                  .GetEntry();
            m_nte_Bert_FwdLimit = m_sbt_Launcher->AddPersistent("Bert Fwd Limit", ConLauncher::BERT_FWD_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(1,0)
                  .GetEntry();
            m_nte_Ernie_RevLimit = m_sbt_Launcher->AddPersistent("Ernie Rev Limit", ConLauncher::ERNIE_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(0,1)
                  .GetEntry();
            m_nte_Bert_RevLimit = m_sbt_Launcher->AddPersistent("Bert Rev Limit", ConLauncher::BERT_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(1,1)
                  .GetEntry();
            m_nte_Ernie_Position = m_sbt_Launcher->AddPersistent("Ernie Pos", ConLauncher::ERNIE_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(0,2)
                  .GetEntry();
            m_nte_Bert_Position = m_sbt_Launcher->AddPersistent("Bert Pos", ConLauncher::BERT_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(1,2)
                  .GetEntry();
            m_nte_Ernie_Power = m_sbt_Launcher->AddPersistent("Ernie Power", ConLauncher::ERNIE_POWER)
                  .WithSize(2,1)
                  .WithPosition(2,0)
                  .GetEntry();
            m_nte_Bert_Power = m_sbt_Launcher->AddPersistent("Bert Power", ConLauncher::BERT_POWER)
                  .WithSize(2,1)
                  .WithPosition(2,1)
                  .GetEntry();

            m_ErnieFwdPower = ConLauncher::ERNIE_POWER;
            m_BertFwdPower = ConLauncher::BERT_POWER;
            // Ensure the launcher is in the retracted position
            Retract();
          }

void Launcher::Launch() {
  LaunchBert();
  LaunchErnie();
}

void Launcher::LaunchBert() {
  printf("Launcher::LaunchBert() Executing...\n");  
  // Launch a ball
  m_launcherMotorBert.Set(m_BertFwdPower);
}

void Launcher::LaunchErnie() {
  printf("Launcher::LaunchErnie() Executing...\n");  
  // Launch a ball
  m_launcherMotorErnie.Set(m_ErnieFwdPower);
}

void Launcher::Retract() {
  // Bring both launchers back
  RetractBert();
  RetractErnie();
}

void Launcher::RetractBert() {
  printf("Launcher::RetractBert() Executing...\n");  
  m_launcherMotorBert.Set(-.1);
}

void Launcher::RetractErnie() {
  printf("Launcher::RetractErnie() Executing...\n");  
  m_launcherMotorErnie.Set(-.1);
}
void Launcher::SetLaunchSoftLimit() {
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Ernie_FwdLimit.GetDouble(115.0));
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 0);
  m_launcherMotorErnie.BurnFlash();
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Bert_FwdLimit.GetDouble(115.0));
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 0);
  m_launcherMotorBert.BurnFlash();
}

void Launcher::SetResetSoftLimit() {}

void Launcher::Stop() {
  m_launcherMotorErnie.Set(0.0);
  m_launcherMotorBert.Set(0.0);
}

void Launcher::Periodic() {
  // Push/Pull stuff from the Network Tables
  m_ErnieFwdPower = m_nte_Ernie_Power.GetDouble(ConLauncher::ERNIE_POWER);
  m_BertFwdPower = m_nte_Bert_Power.GetDouble(ConLauncher::BERT_POWER);
  m_nte_Bert_Position.SetDouble(m_launcherEncoderBert.GetPosition());
  m_nte_Ernie_Position.SetDouble(m_launcherEncoderErnie.GetPosition());
}