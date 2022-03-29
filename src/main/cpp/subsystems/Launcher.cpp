// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/SubsystemBase.h>
#include "subsystems/Launcher.h"
#include "OI.h"

Launcher::Launcher() {
            // Initialize stuff here
    double kP = 6e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000015, kMaxOutput = 1.0, kMinOutput = -1.0;
#ifdef ENABLE_LAUNCHER
#ifdef LAUNCHER_VELOCITY_CONTROL
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
            // All of our Encoders are based on a tick count of 42
            m_launcherEncoderBert.SetPositionConversionFactor(ConSparkMax::POSITION_CONVERSION_FACTOR); // Generally 42
            m_launcherEncoderErnie.SetPositionConversionFactor(ConSparkMax::POSITION_CONVERSION_FACTOR); // Generally 42

            // I believe brake mode is the default, but...
            m_launcherMotorBert.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
            m_launcherMotorErnie.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

            // No hardware limits on these controllers

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
            m_nte_Bert_FarLimit = m_sbt_Launcher->AddPersistent("Bert Far Limit", ConLauncher::BERT_FAR_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(3,0)
                  .GetEntry();
            m_nte_Ernie_FarLimit = m_sbt_Launcher->AddPersistent("Ernie Far Limit", ConLauncher::ERNIE_FAR_LIMIT)
                  .WithSize(1,1)
                  .WithPosition(3,1)
                  .GetEntry();
            m_nte_Bert_Power = m_sbt_Launcher->AddPersistent("Bert Power", ConLauncher::BERT_POWER)
                  .WithSize(1,1)
                  .WithPosition(4,0)
                  .GetEntry();
            m_nte_Ernie_Power = m_sbt_Launcher->AddPersistent("Ernie Power", ConLauncher::ERNIE_POWER)
                  .WithSize(1,1)
                  .WithPosition(4,1)
                  .GetEntry();
            m_nte_Bert_FarPower = m_sbt_Launcher->AddPersistent("Bert Far Power", ConLauncher::BERT_FAR_POWER)
                  .WithSize(1,1)
                  .WithPosition(5,0)
                  .GetEntry();
            m_nte_Ernie_FarPower = m_sbt_Launcher->AddPersistent("Ernie Far Power", ConLauncher::ERNIE_FAR_POWER)
                  .WithSize(1,1)
                  .WithPosition(5,1)
                  .GetEntry();
            m_nte_Bert_Voltage = m_sbt_Launcher->AddPersistent("Bert Voltage", 0.0)
                  .WithSize(2,1)
                  .WithPosition(3,2)
                  .WithWidget(frc::BuiltInWidgets::kDial)
                  .GetEntry();
            m_nte_Ernie_Voltage = m_sbt_Launcher->AddPersistent("Ernie Voltage", 0.0)
                  .WithSize(2,1)
                  .WithPosition(3,3)
                  .WithWidget(frc::BuiltInWidgets::kDial)
                  .GetEntry();

#ifdef LAUNCHER_VELOCITY_CONTROL
  // display PID coefficients on Shuffleboard
  m_nte_Launcher_P__Gain = m_sbt_Launcher->AddPersistent("Launcher P Gain", kP)
                  .WithSize(2,1)
                  .WithPosition(6,0)
                  .GetEntry();
  m_nte_Launcher_I_Gain = m_sbt_Launcher->AddPersistent("Launcher I Gain", kI)
                  .WithSize(2,1)
                  .WithPosition(6,1)
                  .GetEntry();
  m_nte_Launcher_D_Gain = m_sbt_Launcher->AddPersistent("Launcher D Gain", kD)
                  .WithSize(2,1)
                  .WithPosition(6,2)
                  .GetEntry();
  m_nte_Launcher_I_Zone = m_sbt_Launcher->AddPersistent("Launcher Iz Gain", kIz)
                  .WithSize(2,1)
                  .WithPosition(6,4)
                  .GetEntry();
  m_nte_Launcher_Min_Output = m_sbt_Launcher->AddPersistent("Launcher Min Output", kMinOutput)
                  .WithSize(2,1)
                  .WithPosition(8,0)
                  .GetEntry();
  m_nte_Launcher_Max_Output = m_sbt_Launcher->AddPersistent("Launcher Max Output", kMaxOutput)
                  .WithSize(2,1)
                  .WithPosition(8,1)
                  .GetEntry();
  m_nte_Launcher_Feed_Forward = m_sbt_Launcher->AddPersistent("Launcher Feed Forward", kFF)
                  .WithSize(2,1)
                  .WithPosition(8,3)
                  .GetEntry();
#endif

            m_ErnieFwdPower = ConLauncher::ERNIE_POWER;
            m_BertFwdPower = ConLauncher::BERT_POWER;
            m_ErnieFarPower = ConLauncher::ERNIE_FAR_POWER;
            m_BertFarPower = ConLauncher::BERT_FAR_POWER;

            // Ensure the launcher is in the retracted position
            Retract();
          }

void Launcher::Launch() {
  LaunchBert();
  LaunchErnie();
}

void Launcher::LaunchBert() {
  printf("Launcher::LaunchBert() Executing... Power %f Limit %f\n", 
    m_useClose ? m_BertFwdPower : m_BertFarPower,
    m_useClose ? m_BertFwdLimit : m_BertFarLimit);
  // Launch a ball
#ifdef ENABLE_LAUNCHER
  if (m_useClose) {
    m_launcherMotorBert.Set(m_BertFwdPower);
  } else {
    m_launcherMotorBert.Set(m_BertFarPower);
  }
#endif
}

void Launcher::LaunchErnie() {
  printf("Launcher::LaunchErnie() Executing...Power %f Limit %f\n",
    m_useClose ? m_ErnieFwdPower : m_ErnieFarPower,
    m_useClose ? m_ErnieFwdLimit : m_ErnieFarLimit); 
  // Launch a ball
#ifdef ENABLE_LAUNCHER
  if (m_useClose) {
    m_launcherMotorErnie.Set(m_ErnieFwdPower);
  } else {
    m_launcherMotorErnie.Set(m_ErnieFarPower);
  }
#endif
}

void Launcher::Retract() {
  // Bring both launchers back
  RetractBert();
  RetractErnie();
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

void Launcher::SetupFar(){
  printf("Launcher::SetupFar()\n");
  m_useClose = false;
#ifdef ENABLE_LAUNCHER
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_ErnieFarLimit);
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_BertFarLimit);
#endif // ENABLE_LAUNCHER
}

void Launcher::SetupClose() {
  printf("Launcher::SetupClose()\n");
  m_useClose = true;
#ifdef ENABLE_LAUNCHER
  m_launcherMotorErnie.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_ErnieFwdLimit);
  m_launcherMotorBert.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_BertFwdLimit);
#endif // ENABLE_LAUNCHER
}

void Launcher::SetLaunchSoftLimits() {
  double d;

  // Close Power
  d = m_nte_Ernie_Power.GetDouble(ConLauncher::ERNIE_POWER);
  if (d != m_ErnieFwdPower) {
    m_ErnieFwdPower = d;
    printf("m_ErnieFwdPower set to %f\n", m_ErnieFwdPower);
  }
  d = m_nte_Bert_Power.GetDouble(ConLauncher::BERT_POWER);
  if (d != m_BertFwdPower) {
    m_BertFwdPower = d;
    printf("m_BertFwdPower set to %f\n", m_BertFwdPower);
  }

  // Close Limits
  d = m_nte_Ernie_FwdLimit.GetDouble(ConLauncher::ERNIE_FWD_LIMIT);
  if (d != m_ErnieFwdLimit) {
    m_ErnieFwdLimit = d;
    printf("m_ErnieFwdLimit set to %f\n", m_ErnieFwdLimit);
  }
  d = m_nte_Bert_FwdLimit.GetDouble(ConLauncher::BERT_FWD_LIMIT);
  if (d != m_BertFwdLimit) {
    m_BertFwdLimit = d;
    printf("m_BertFwdLimit set to %f\n", m_BertFwdLimit);
  }

  // Far Power
  d = m_nte_Ernie_FarPower.GetDouble(ConLauncher::ERNIE_FAR_POWER);
  if (d != m_ErnieFarPower) {
    m_ErnieFarPower = d;
    printf("m_ErnieFarPower set to %f\n", m_ErnieFarPower);
  }
  d = m_nte_Bert_FarPower.GetDouble(ConLauncher::BERT_FAR_POWER);
  if (d != m_BertFarPower) {
    m_BertFarPower = d;
    printf("m_BertFarPower set to %f\n", m_BertFarPower);
  }

  // Far Limits
  d = m_nte_Ernie_FarLimit.GetDouble(ConLauncher::ERNIE_FAR_LIMIT);
  if (d != m_ErnieFarLimit) {
    m_ErnieFarLimit = d;
    printf("m_ErnieFarLimit set to %f\n", m_ErnieFarLimit);
  }
  d = m_nte_Bert_FarLimit.GetDouble(ConLauncher::BERT_FAR_LIMIT);
  if (d != m_BertFarLimit) {
    m_BertFarLimit = d;
    printf("m_BertFarLimit set to %f\n", m_BertFarLimit);
  }
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
#ifdef ENABLE_LAUNCHER
  // Display
  m_nte_Bert_Position.SetDouble(m_launcherEncoderBert.GetPosition());
  m_nte_Ernie_Position.SetDouble(m_launcherEncoderErnie.GetPosition());
  m_nte_Bert_Voltage.SetDouble(m_launcherMotorErnie.GetBusVoltage());
  m_nte_Ernie_Voltage.SetDouble(m_launcherMotorErnie.GetBusVoltage());
#endif
}

void Launcher::BurnFlash() {
  printf("BurnFlash for Launchers\n");
#ifdef ENABLE_LAUNCHER
  // Save the configuration to flash memory
  m_launcherMotorErnie.BurnFlash();
  m_launcherMotorBert.BurnFlash();
#endif // ENABLE_LAUNCHER
}
