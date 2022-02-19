// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>

#include "env.h"

namespace ConLauncher {
  constexpr int MOTOR_BERT_ID = 6;
  constexpr int MOTOR_ERNIE_ID = 1;
  // Starting point for Launcher soft limits
  constexpr int BERT_FWD_LIMIT = 185;
  constexpr int ERNIE_FWD_LIMIT = 190;
  constexpr int BERT_REV_LIMIT = 0;
  constexpr int ERNIE_REV_LIMIT = 0;
  constexpr double BERT_RAMP_RATE = .1;
  constexpr double ERNIE_RAMP_RATE = .1;
  constexpr double BERT_POWER = .45;
  constexpr double ERNIE_POWER = .45;
  constexpr int CURRENT_STALL_LIMIT = 80;
}

class Launcher : public frc2::SubsystemBase {
 public:
  Launcher();
  void LaunchBert();
  void LaunchErnie();
  void Launch(); // Launch both Bert & Ernie
  void RetractBert();
  void RetractErnie();
  void Retract(); // Move both catapaults back to starting position
  void Stop(); // Stop launcher motors
  void SetLaunchSoftLimits();
  void SetResetSoftLimits();

  frc::ShuffleboardTab *m_sbt_Launcher;
  // Inputs from Dashboard
  nt::NetworkTableEntry m_nte_Bert_FwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_Bert_RevLimit; // Ditto for the reverse
  nt::NetworkTableEntry m_nte_Ernie_FwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_Ernie_RevLimit; // Ditto for the reverse
  nt::NetworkTableEntry m_nte_Ernie_Power; // 0.0 to 1.0 (max)
  nt::NetworkTableEntry m_nte_Bert_Power; // Ditto
  nt::NetworkTableEntry m_nte_Bert_Ramp_Rate;
  nt::NetworkTableEntry m_nte_Ernie_Ramp_Rate;

  // Outputs to Dashboard
  nt::NetworkTableEntry m_nte_Ernie_Position; // Encoder feedback
  nt::NetworkTableEntry m_nte_Bert_Position; // Ditto

 protected:
 #ifdef ENABLE_LAUNCHER
  // NEO motor
  rev::CANSparkMax m_launcherMotorBert{ConLauncher::MOTOR_BERT_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_launcherMotorErnie{ConLauncher::MOTOR_ERNIE_ID, rev::CANSparkMax::MotorType::kBrushless};

  // built-in encoders
  rev::SparkMaxRelativeEncoder m_launcherEncoderBert = m_launcherMotorBert.GetEncoder();
  rev::SparkMaxRelativeEncoder m_launcherEncoderErnie = m_launcherMotorErnie.GetEncoder();
 #endif
  // Power Settings for each launcher
  double m_ErnieFwdPower;
  double m_BertFwdPower;

  void Periodic();
};
