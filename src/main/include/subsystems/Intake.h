// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include <frc/Timer.h>
#include <rev/CANSparkMax.h>

namespace ConIntake {
  constexpr int MOTOR_ID = 9;
  constexpr int PNEUM_PORT_A = 0;
  constexpr int PNEUM_PORT_B = 1;
  constexpr double LOAD_BALL = 1.0; // Should be motor forward
  constexpr double REJECT_BALL = -1.0; // Should be motor reverse
  constexpr int CURRENT_STALL_LIMIT = 40;
  constexpr double INTAKE_POWER = 1.0; // Up from 60% power
  constexpr units::time::second_t SHUTDOWN_DELAY = 1.0_s; // Seconds to delay between Stow() and motor shutdown
}

class Intake : public frc2::SubsystemBase {
 public:
  Intake();
  void ToggleDeployedState();
  void Deploy();
  void Stow();
  void Load();
  void Reject();
  void Periodic() override;

  frc::ShuffleboardTab *m_sbt_Intake;
  nt::NetworkTableEntry m_nte_MotorCurrent;
  nt::NetworkTableEntry m_nte_StowedState;
  nt::NetworkTableEntry m_nte_MotorPower;
  nt::NetworkTableEntry m_nte_ShutdownDelay;

 protected:
  frc::DoubleSolenoid deployDoublePCM{frc::PneumaticsModuleType::CTREPCM, ConIntake::PNEUM_PORT_A, ConIntake::PNEUM_PORT_B};
  rev::CANSparkMax m_intakeMotor {ConIntake::MOTOR_ID, rev::CANSparkMax::MotorType::kBrushed}; // Regular brushed motor
  // Brushed motor - No sensor
  // rev::SparkMaxRelativeEncoder m_intakeEncoder = m_intakeMotor.GetEncoder();
  bool m_deployedState; // True if intake system is deployed outside of robot perimeter
  double m_intakePower; // Power to run intake motor
  frc::Timer m_timer;
};
