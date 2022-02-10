// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>

#include "env.h"

namespace ConLauncher {
  constexpr int MOTOR_BERT_ID = 6;
  constexpr int MOTOR_ERNIE_ID = 1;
  // Starting point for Launcher soft limits
  constexpr int BERT_FWD_LIMIT = 115;
  constexpr int ERNIE_FWD_LIMIT = 115;
  constexpr int BERT_REV_LIMIT = -5;
  constexpr int ERNIE_REV_LIMIT = -5;
  constexpr int CURRENT_STALL_LIMIT = 80;
}

class Launcher : public frc2::PIDSubsystem {
 public:
  Launcher();
  void LaunchBert();
  void LaunchErnie();
  void Launch(); // Launch both Bert & Ernie
  void RetractBert();
  void RetractErnie();
  void Retract(); // Move both catapaults back to starting position
  void Reset();
  void SetLaunchSoftLimit();
  void SetResetSoftLimit();

  frc::ShuffleboardTab *m_sbt_Launcher;
  nt::NetworkTableEntry m_nte_Bert_FwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_Bert_RevLimit; // Ditto for the reverse
  nt::NetworkTableEntry m_nte_Ernie_FwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_Ernie_RevLimit; // Ditto for the reverse

 protected:
 #ifdef ENABLE_LAUNCHER
  // NEO motor
  rev::CANSparkMax m_launcherMotorBert{ConLauncher::MOTOR_BERT_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_launcherMotorErnie{ConLauncher::MOTOR_ERNIE_ID, rev::CANSparkMax::MotorType::kBrushless};

  // built-in encoders
  rev::SparkMaxRelativeEncoder m_launcherEncoderBert = m_launcherMotorBert.GetEncoder();
  rev::SparkMaxRelativeEncoder m_launcherEncoderErnie = m_launcherMotorErnie.GetEncoder();
 #endif
  void UseOutput(double output, double setpoint) override;

  double GetMeasurement() override;
};
