// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include "OI.h"
#include "Constants.h"

Climber::Climber()
    : PIDSubsystem(
          // The PIDController used by the subsystem
          frc2::PIDController(0, 0, 0)) {

    // Initialize Shuffleboard Tab and Network Table Entries
    m_sbt_Climber = &frc::Shuffleboard::GetTab(ConShuffleboard::ClimberTab);

    m_nte_ClimberDistance = m_sbt_Climber->AddPersistent("Climber Position", 0.0)
          .WithSize(2,1)
          .WithPosition(0,0)
          .GetEntry();
    m_nte_ClimberOutput = m_sbt_Climber->AddPersistent("Climber Output", 0.0)
          .WithSize(2,1)
          .WithPosition(0,1)
          .GetEntry();
    m_nte_ClimbSpeedLimit = m_sbt_Climber->AddPersistent("Climb Speed Limit", ConClimber::CLIMB_SPEED)
          .WithSize(2,1)
          .WithPosition(2,0)
          .GetEntry();
    m_nte_DescendSpeedLimit = m_sbt_Climber->AddPersistent("Descend Speed Limit", ConClimber::DESCEND_SPEED)
          .WithSize(2,1)
          .WithPosition(2,1)
          .GetEntry();
    m_nte_ExtendLimit = m_sbt_Climber->AddPersistent("Extension Limit", ConClimber::SOFT_LIMIT_FWD)
          .WithSize(2,1)
          .WithPosition(2,2)
          .GetEntry();
    m_nte_RetractLimit = m_sbt_Climber->AddPersistent("Retract Limit", ConClimber::SOFT_LIMIT_REV)
          .WithSize(2,1)
          .WithPosition(2,3)
          .GetEntry();


#ifdef ENABLE_CLIBMER
    m_climberMotor.SetSmartCurrentLimit(ConClimber::CURRENT_STALL_LIMIT, ConClimber::CURRENT_STALL_LIMIT);
    m_climberEncoder.SetPositionConversionFactor(ConSparkMax::POSITION_CONVERSION_FACTOR); // Generally 42
    m_climberMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    // Reset Encoder to zero for starting configuration
    m_climberEncoder.SetPosition(0.0);
    // Configure SparkMax SoftLimits
    m_climberMotor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);
    m_climberMotor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, ConClimber::SOFT_LIMIT_FWD);
    m_climberMotor.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    m_climberMotor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, ConClimber::SOFT_LIMIT_REV);
    m_climberMotor.BurnFlash();
#endif 
    }

void Climber::UseOutput(double output, double setpoint) {
  // Use the output here
}

double Climber::GetMeasurement() {
  // Return the process variable measurement here
  return 0;
}

// Climb lifts the robot up to target position
void Climber::Climb() {
#ifdef ENABLE_CLIMBER
    m_climberMotor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, m_nte_ExtendLimit.GetDouble(ConClimber::SOFT_LIMIT_FWD));
    m_climberMotor.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, m_nte_ExtendLimit.GetDouble(ConClimber::SOFT_LIMIT_REV));
    m_climberMotor.BurnFlash();
    m_climberMotor.Set(m_nte_ClimbSpeedLimit.GetDouble(ConClimber::CLIMB_SPEED));
#endif
}

// Descend is a manual override to lower the robot
void Climber::Extend() {
#ifdef ENABLE_CLIMBER
  m_climberMotor.Set(m_nte_DescendSpeedLimit.GetDouble(ConClimber::DESCEND_SPEED));
#endif
}

void Climber::Stop() {
#ifdef ENABLE_CLIMBER
  m_climberMotor.Set(0.0);
#endif
}

void Climber::Periodic() {
#ifdef ENABLE_CLIMBER
  m_nte_ClimberDistance.SetDouble(m_climberEncoder.GetPosition());
  m_nte_ClimberOutput.SetDouble(m_climberEncoder.GetVelocity());
#endif
}

