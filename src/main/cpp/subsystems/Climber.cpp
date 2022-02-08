// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Climber.h"
#include "OI.h"

Climber::Climber()
    : PIDSubsystem(
          // The PIDController used by the subsystem
          frc2::PIDController(0, 0, 0)) {

    m_sbt_Climber = &frc::Shuffleboard::GetTab(ConShuffleboard::ClimberTab);

    m_nte_ClimberDistance = m_sbt_Climber->AddPersistent("Climber Position", 0.0)
          .WithSize(2,1)
          .WithPosition(0,0)
          .GetEntry();
    m_nte_ClimberOutput = m_sbt_Climber->AddPersistent("Climber Output", 0.0)
          .WithSize(2,1)
          .WithPosition(0,1)
          .GetEntry();
    m_nte_ClimbSpeed = m_sbt_Climber->AddPersistent("Climb Speed (-1.0 - 0.0)", ConClimber::CLIMB_SPEED)
          .WithSize(2,1)
          .WithPosition(0,2)
          .GetEntry();
    m_nte_DescendSpeed = m_sbt_Climber->AddPersistent("Descend Speed (0.0 - 1.0)", ConClimber::DESCEND_SPEED)
          .WithSize(2,1)
          .WithPosition(0,3)
          .GetEntry();
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
  m_climberMotor.Set(ConClimber::CLIMB_SPEED);
}

// Descend is a manual override to lower the robot
void Climber::Descend() {
  m_climberMotor.Set(ConClimber::DESCEND_SPEED);
}

void Climber::Stop() {
  m_climberMotor.Set(0.0);
}
// Engage/Disengage chain locking mechanism
/* This can either go away or will become pneumatically actuated
void Climber::Lock() {
  chainLock.SetAngle(0.0);
  m_nte_LockStatus.SetBoolean(true);
}

void Climber::Unlock() {
  chainLock.SetAngle(180.0);
  m_nte_LockStatus.SetBoolean(false);
}
*/

void Climber::Periodic() {
// FIXME: Uncomment when ready
//  m_nte_ClimberDistance.SetDouble(m_climberEncoder.GetPosition());
//  m_nte_ClimberSpeed.SetDouble(m_climberEncoder.GetVelocity());
  
  /*
  if (m_nte_LockToggle.GetBoolean(true)) {
    Lock();
  } 
  else {
    Unlock();
  }
  */
}

