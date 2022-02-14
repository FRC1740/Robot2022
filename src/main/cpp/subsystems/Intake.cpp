// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Intake.h"
#include "Constants.h"

Intake::Intake() {
        // Initialize the DoubleSolenoid so it knows where to start.  Not required for single solenoids.
        deployDoublePCM.Set(frc::DoubleSolenoid::Value::kReverse);
        m_deployedState = false;

        // DONT Configure SparkMax settings for BRUSHED motor. Use Rev Software
        // m_intakeMotor.SetSmartCurrentLimit(ConIntake::CURRENT_STALL_LIMIT, ConIntake::CURRENT_STALL_LIMIT);
        //m_intakeEncoder.SetPositionConversionFactor(ConSparkMax::POSITION_CONVERSION_FACTOR); // Generally 42
        //m_intakeMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
        // Save SparkMax motor/encoder config to flash memory
        //m_intakeMotor.BurnFlash();
        }

void Intake::Deploy() {
  deployDoublePCM.Set(frc::DoubleSolenoid::Value::kForward);
  m_deployedState = true;
  Load();
}

void Intake::Stow() {
  deployDoublePCM.Set(frc::DoubleSolenoid::Value::kReverse);
  m_intakeMotor.Set(0.0);
  m_deployedState = false;
}

void Intake::Load() {
  printf("Intake::Load() Executing...\n");
  if (m_deployedState) {
    m_intakeMotor.Set(ConIntake::LOAD_BALL);
  } else {
    m_intakeMotor.Set(0.0);
  }
}

void Intake::Reject() {
  printf("Intake::Reject() Executing...\n");
  if (m_deployedState) {
    m_intakeMotor.Set(ConIntake::REJECT_BALL);
  } else {
    m_intakeMotor.Set(0.0);
  }
}
