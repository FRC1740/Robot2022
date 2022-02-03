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
    m_nte_ClimberSpeed = m_sbt_Climber->AddPersistent("Climber Speed", 0.0)
          .WithSize(2,1)
          .WithPosition(0,1)
          .GetEntry();
    m_nte_LockStatus = m_sbt_Climber->AddPersistent("Chain Locked?", false)
          .WithSize(1,1)
          .WithPosition(2,0)
          .WithWidget(frc::BuiltInWidgets::kBooleanBox)
          .GetEntry();
    m_nte_LockToggle = m_sbt_Climber->AddPersistent("Lock/Unlock", false)
          .WithSize(1,1)
          .WithPosition(2,1)
          .WithWidget(frc::BuiltInWidgets::kToggleButton)
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

}

// Descend is a manual override to lower the robot
void Climber::Descend() {

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

