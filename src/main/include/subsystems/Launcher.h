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
  constexpr int LAUNCHER_MOTOR_BERT_ID = 6;
  constexpr int LAUNCHER_MOTOR_ERNIE_ID = 1;
}

class Launcher : public frc2::PIDSubsystem {
 public:
  Launcher();
  void LaunchBert();
  void LaunchErnie();
  void Launch(); // Launch both Bert & Ernie
  void Reset();
  void SetLaunchSoftLimit();
  void SetResetSoftLimit();

  frc::ShuffleboardTab *m_sbt_Launcher;
  nt::NetworkTableEntry m_nte_LaunchBert_FwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_LaunchBert_RevLimit; // Ditto for the reverse
  nt::NetworkTableEntry m_nte_LaunchErnie_FwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_LaunchErnie_RevLimit; // Ditto for the reverse

 protected:
 #ifdef ENABLE_LAUNCHER
  // NEO motor
  rev::CANSparkMax m_launcherMotorBert{ConLauncher::LAUNCHER_MOTOR_BERT_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_launcherMotorErnie{ConLauncher::LAUNCHER_MOTOR_ERNIE_ID, rev::CANSparkMax::MotorType::kBrushless};

  // built-in encoders
  rev::SparkMaxRelativeEncoder m_launcherEncoderBert = m_launcherMotorBert.GetEncoder();
  rev::SparkMaxRelativeEncoder m_launcherEncoderErnie = m_launcherMotorErnie.GetEncoder();
 #endif
  void UseOutput(double output, double setpoint) override;

  double GetMeasurement() override;
};
