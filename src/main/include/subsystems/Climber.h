// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include <rev/CANSparkMax.h>
#include "Constants.h"

namespace ConClimber {
  // Motor
  constexpr int CLIMBER_MOTOR_ID = 8;

  //Spark Max Settings
  constexpr int RAMP_RATE = 0.100; //seconds
  constexpr bool INVERTED = true; //
  constexpr bool NONINVERTED = false; //
  constexpr double CLIMB_SPEED = -1.0;  // Climb Motor Speed
  constexpr double DESCEND_SPEED = 1.0; // Descend Motor Speed
  constexpr int SOFT_LIMIT_FWD = 4784; // Soft Limit Extension 5' 6" MAX height; Bar @ 60-1/4"
  constexpr int SOFT_LIMIT_REV = 200;
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
  void SetClimberSoftLimits();
  void BurnFlash();

  frc::ShuffleboardTab *m_sbt_Climber;
  nt::NetworkTableEntry m_nte_ClimberDistance;
  nt::NetworkTableEntry m_nte_ClimberOutput;
  nt::NetworkTableEntry m_nte_ClimbSpeedLimit;
  nt::NetworkTableEntry m_nte_DescendSpeedLimit;
  nt::NetworkTableEntry m_nte_ExtendLimit;
  nt::NetworkTableEntry m_nte_RetractLimit;
  nt::NetworkTableEntry m_nte_MotorCurrent;
  double m_softLimitFwd = ConClimber::SOFT_LIMIT_FWD;
  double m_softLimitRev = ConClimber::SOFT_LIMIT_REV;

 protected:

  void UseOutput(double output, double setpoint) override;
  double GetMeasurement() override;
  void Periodic();

#ifdef ENABLE_CLIMBER
  // Neo motor controllers
  rev::CANSparkMax m_climberMotor {ConClimber::CLIMBER_MOTOR_ID, rev::CANSparkMax::MotorType::kBrushless};
  // Drive encoders
  rev::SparkMaxRelativeEncoder m_climberEncoder = m_climberMotor.GetEncoder();
#endif // ENABLE_CLIMBER
};
