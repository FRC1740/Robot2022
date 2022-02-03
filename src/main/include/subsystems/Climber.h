// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/Servo.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include <rev/CANSparkMax.h>

namespace ConClimber {
  // Motor
  constexpr int CLIMBER_MOTOR_ID = 1;

  //Spark Max Settings
  constexpr int RAMP_RATE = 0.100; //seconds
  constexpr bool INVERTED = true; //
  constexpr bool NONINVERTED = false; //

  //Servo
  constexpr int kServoPWMPort = 9;
}


class Climber : public frc2::PIDSubsystem {
 public:
  Climber();

  void Climb();
  void Descend();
  /*
  void Lock();
  void Unlock();
  */

  frc::ShuffleboardTab *m_sbt_Climber;
  nt::NetworkTableEntry m_nte_ClimberDistance;
  nt::NetworkTableEntry m_nte_ClimberSpeed;
  nt::NetworkTableEntry m_nte_LockToggle;
  nt::NetworkTableEntry m_nte_LockStatus;

 protected:

  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  void Periodic();

  /*
  // Neo motor controllers
  rev::CANSparkMax m_climberMotor {ConClimber::CLIMBER_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  // Drive encoders
  rev::SparkMaxRelativeEncoder m_climberEncoder = m_climberMotor.GetEncoder();
  */
  // Locking Servo
  // frc::Servo chainLock {ConClimber::kServoPWMPort};

};
