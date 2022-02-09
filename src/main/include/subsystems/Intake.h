// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Relay.h>
#include <rev/CANSparkMax.h>
#include <frc/Servo.h>

namespace ConIntake {
  constexpr int MOTOR_ID = 7;
  constexpr int RELAY_PORT = 0; // Testing: Not used on actual robot
  constexpr int PNEUM_PORT_A = 0;
  constexpr int PNEUM_PORT_B = 1;
  constexpr double LOAD_BALL = 1.0; // Should be motor forward
  constexpr double REJECT_BALL = -1.0; // Should be motor reverse
  constexpr int SERVO_PORT = 2; // Testing: Not used on actual robot
}

class Intake : public frc2::PIDSubsystem {
 public:
  Intake();
  void Deploy();
  void Stow();
  void Load();
  void Reject();
  void TestRelay(int);
  void TestServo(int);

 protected:
  void UseOutput(double output, double setpoint) override;

  double GetMeasurement() override;

  frc::DoubleSolenoid deployDoublePCM{frc::PneumaticsModuleType::CTREPCM, ConIntake::PNEUM_PORT_A, ConIntake::PNEUM_PORT_B};
  rev::CANSparkMax m_intakeMotor {ConIntake::MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  frc::Relay testRelay {ConIntake::RELAY_PORT};
  frc::Relay::Value m_relayDirection;
  frc::Servo testServo {ConIntake::SERVO_PORT};
  bool m_deployedState; // True if intake system is deployed outside of robot perimeter
};
