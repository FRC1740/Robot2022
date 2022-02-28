// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/SubsystemBase.h>
#include "subsystems/Launcher.h"
#include "OI.h"

Launcher::Launcher() {
            // Initialize stuff here
            #ifdef ENABLE_LAUNCHER
#ifdef LAUNCHER_VELOCITY_CONTROL
double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;
    m_launcherMotorBert.RestoreFactoryDefaults();
    m_launcherMotorErnie.RestoreFactoryDefaults();
    
    // set PID coefficients
    m_pidControllerBert.SetP(kP);
    m_pidControllerBert.SetI(kI);
    m_pidControllerBert.SetD(kD);
    m_pidControllerBert.SetIZone(kIz);
    m_pidControllerBert.SetFF(kFF);
    m_pidControllerBert.SetOutputRange(kMinOutput, kMaxOutput);

    m_pidControllerErnie.SetP(kP);
    m_pidControllerErnie.SetI(kI);
    m_pidControllerErnie.SetD(kD);
    m_pidControllerErnie.SetIZone(kIz);
    m_pidControllerErnie.SetFF(kFF);
    m_pidControllerErnie.SetOutputRange(kMinOutput, kMaxOutput);
#endif
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

            // Robot outputs -> Shuffleboard
            m_nte_Bert_Position = m_sbt_Launcher->AddPersistent("Bert Pos", ConLauncher::BERT_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(0,0)
                  .GetEntry();
            m_nte_Ernie_Position = m_sbt_Launcher->AddPersistent("Ernie Pos", ConLauncher::ERNIE_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(0,1)
                  .GetEntry();

            // Robot inputs <- Shuffleboard
            m_nte_Bert_FwdLimit = m_sbt_Launcher->AddPersistent("Bert Fwd Limit", ConLauncher::BERT_FWD_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(2,0)
                  .GetEntry();
            m_nte_Ernie_FwdLimit = m_sbt_Launcher->AddPersistent("Ernie Fwd Limit", ConLauncher::ERNIE_FWD_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(2,1)
                  .GetEntry();
            m_nte_Bert_RevLimit = m_sbt_Launcher->AddPersistent("Bert Rev Limit", ConLauncher::BERT_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(3,0)
                  .GetEntry();
            m_nte_Ernie_RevLimit = m_sbt_Launcher->AddPersistent("Ernie Rev Limit", ConLauncher::ERNIE_REV_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(3,1)
                  .GetEntry();
            m_nte_Bert_Power = m_sbt_Launcher->AddPersistent("Bert Power", ConLauncher::BERT_POWER)
                  .WithSize(2,1)
                  .WithPosition(4,0)
                  .GetEntry();
            m_nte_Ernie_Power = m_sbt_Launcher->AddPersistent("Ernie Power", ConLauncher::ERNIE_POWER)
                  .WithSize(2,1)
                  .WithPosition(4,1)
                  .GetEntry();
            m_nte_Bert_Voltage = m_sbt_Launcher->AddPersistent("Bert Voltage", 0.0)
                  .WithSize(2,1)
                  .WithPosition(4,2)
                  .WithWidget(frc::BuiltInWidgets::kDial)
                  .GetEntry();
            m_nte_Ernie_Voltage = m_sbt_Launcher->AddPersistent("Ernie Voltage", 0.0)
                  .WithSize(2,1)
                  .WithPosition(4,3)
                  .WithWidget(frc::BuiltInWidgets::kDial)
                  .GetEntry();

#ifdef LAUNCHER_VELOCITY_CONTROL
  // display PID coefficients on Shuffleboard
  m_nte_Launcher_P__Gain = m_sbt_Launcher->AddPersistent("Launcher P Gain", kP)
                  .WithSize(2,1)
                  .WithPosition(5,0)
                  .GetEntry();
  m_nte_Launcher_I_Gain = m_sbt_Launcher->AddPersistent("Launcher I Gain", kI)
                  .WithSize(2,1)
                  .WithPosition(5,1)
                  .GetEntry();
  m_nte_Launcher_D_Gain = m_sbt_Launcher->AddPersistent("Launcher D Gain", kD)
                  .WithSize(2,1)
                  .WithPosition(5,2)
                  .GetEntry();
  m_nte_Launcher_I_Zone = m_sbt_Launcher->AddPersistent("Launcher I Gain", kIz)
                  .WithSize(2,1)
                  .WithPosition(5,3)
                  .GetEntry();
  m_nte_Launcher_Feed_Forward = m_sbt_Launcher->AddPersistent("Launcher Feed Forward", kFF)
                  .WithSize(2,1)
                  .WithPosition(6,0)
                  .GetEntry();
  m_nte_Launcher_Max_Output = m_sbt_Launcher->AddPersistent("Launcher Max Output", kMaxOutput)
                  .WithSize(2,1)
                  .WithPosition(6,1)
                  .GetEntry();
  m_nte_Launcher_Min_Output = m_sbt_Launcher->AddPersistent("Launcher Min Output", kMinOutput)
                  .WithSize(2,1)
                  .WithPosition(6,2)
                  .GetEntry();
#endif

            m_ErnieFwdPower = ConLauncher::ERNIE_POWER;
            m_BertFwdPower = ConLauncher::BERT_POWER;

            #ifdef ENABLE_LAUNCHER
            // Ensure the launcher is in the retracted position
            Retract();
            #endif
          }

void Launcher::Launch() {
  #ifdef ENABLE_LAUNCHER
  LaunchBert();
  LaunchErnie();
  #endif
}

void Launcher::LaunchBert() {
  printf("Launcher::LaunchBert() Executing...\n");  
  // Launch a ball
  #ifdef ENABLE_LAUNCHER
  m_launcherMotorBert.Set(m_BertFwdPower);
  #endif
}

void Launcher::LaunchErnie() {
  printf("Launcher::LaunchErnie() Executing...\n");  
  // Launch a ball
  #ifdef ENABLE_LAUNCHER
  m_launcherMotorErnie.Set(m_ErnieFwdPower);
  #endif
}

void Launcher::Retract() {
  // Bring both launchers back
  #ifdef ENABLE_LAUNCHER
  RetractBert();
  RetractErnie();
  #endif
}

void Launcher::RetractBert() {
  printf("Launcher::RetractBert() Executing...\n");  
  #ifdef ENABLE_LAUNCHER
  m_launcherMotorBert.Set(-.1);
  #endif
}

void Launcher::RetractErnie() {
  printf("Launcher::RetractErnie() Executing...\n");  
  #ifdef ENABLE_LAUNCHER
  m_launcherMotorErnie.Set(-.1);
  #endif
}

void Launcher::SetLaunchSoftLimits() {
  #ifdef ENABLE_LAUNCHER
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Ernie_FwdLimit.GetDouble(ConLauncher::ERNIE_FWD_LIMIT));
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, m_nte_Ernie_RevLimit.GetDouble(ConLauncher::ERNIE_REV_LIMIT));
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_Bert_FwdLimit.GetDouble(ConLauncher::BERT_FWD_LIMIT));
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, m_nte_Bert_RevLimit.GetDouble(ConLauncher::BERT_REV_LIMIT));
  m_launcherMotorBert.BurnFlash();  
  #endif
}

void Launcher::SetResetSoftLimits() {
}

void Launcher::Stop() {
  #ifdef ENABLE_LAUNCHER
  m_launcherMotorErnie.Set(0.0);
  m_launcherMotorBert.Set(0.0);
  #endif
}

void Launcher::Periodic() {
  // Push/Pull stuff from the Network Tables
  #ifdef ENABLE_LAUNCHER
  m_ErnieFwdPower = m_nte_Ernie_Power.GetDouble(ConLauncher::ERNIE_POWER);
  m_BertFwdPower = m_nte_Bert_Power.GetDouble(ConLauncher::BERT_POWER);
  m_nte_Bert_Position.SetDouble(m_launcherEncoderBert.GetPosition());
  m_nte_Ernie_Position.SetDouble(m_launcherEncoderErnie.GetPosition());
  // Display
  m_nte_Bert_Voltage.SetDouble(m_launcherMotorErnie.GetBusVoltage());
  m_nte_Ernie_Voltage.SetDouble(m_launcherMotorErnie.GetBusVoltage());
  #endif
}