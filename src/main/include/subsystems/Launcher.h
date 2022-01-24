// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

namespace ConLauncher {
  constexpr int LAUNCHER_MOTOR_ID = 6;
}

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>

class Launcher : public frc2::PIDSubsystem {
 public:
  Launcher();
  void Launch();
  void Reset();
  void SetLaunchSoftLimit();
  void SetResetSoftLimit();

  frc::ShuffleboardTab *m_sbt_Launcher;
  nt::NetworkTableEntry m_nte_LaunchFwdLimit; // LAUNCHER forward may be MOTOR REVERSE!!!
  nt::NetworkTableEntry m_nte_LaunchRevLimit; // Ditto for the reverse

 protected:
  // NEO motor
  rev::CANSparkMax m_launcherMotor{ConLauncher::LAUNCHER_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};

  // built-in encoder
  rev::SparkMaxRelativeEncoder m_launcherEncoder = m_launcherMotor.GetEncoder();

  void UseOutput(double output, double setpoint) override;

  double GetMeasurement() override;
};
