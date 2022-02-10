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
  constexpr int CLIMBER_MOTOR_ID = 8;

  //Spark Max Settings
  constexpr int RAMP_RATE = 0.100; //seconds
  constexpr bool INVERTED = true; //
  constexpr bool NONINVERTED = false; //
  constexpr double CLIMB_SPEED = -1.0;  // Climb Motor Speed
  constexpr double DESCEND_SPEED = 1.0; // Descend Motor Speed
  constexpr int SOFT_LIMIT_FWD = 2000; // Soft Limit Extension 5' 6" MAX height
  constexpr int SOFT_LIMIT_REV = 20;
  constexpr int CURRENT_STALL_LIMIT = 80;

  //Servo
  constexpr int kServoPWMPort = 9;
}


class Climber : public frc2::PIDSubsystem {
 public:
  Climber();

  void Climb();
  void Extend();
  void Stop();
  
  frc::ShuffleboardTab *m_sbt_Climber;
  nt::NetworkTableEntry m_nte_ClimberDistance;
  nt::NetworkTableEntry m_nte_ClimberOutput;
  nt::NetworkTableEntry m_nte_ClimbSpeedLimit;
  nt::NetworkTableEntry m_nte_DescendSpeedLimit;
  nt::NetworkTableEntry m_nte_ExtendLimit;
  nt::NetworkTableEntry m_nte_RetractLimit;

 protected:

  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  void Periodic();

  
  // Neo motor controllers
  rev::CANSparkMax m_climberMotor {ConClimber::CLIMBER_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  // Drive encoders
  rev::SparkMaxRelativeEncoder m_climberEncoder = m_climberMotor.GetEncoder();
  
};
