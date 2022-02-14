// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Intake.h"
#include "Constants.h"
#include "OI.h"

Intake::Intake() {
        // Initialize the DoubleSolenoid so it knows where to start.  Not required for single solenoids.
        deployDoublePCM.Set(frc::DoubleSolenoid::Value::kReverse);
        m_deployedState = false;

        m_intakeMotor.SetSmartCurrentLimit(ConIntake::CURRENT_STALL_LIMIT, ConIntake::CURRENT_STALL_LIMIT);
        m_intakeMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
        // Save SparkMax motor/encoder config to flash memory
        m_intakeMotor.BurnFlash();

        // No encoder on brushed motor
        //m_intakeEncoder.SetPositionConversionFactor(ConSparkMax::POSITION_CONVERSION_FACTOR); // Generally 42

        // Initialize Shuffleboard Tab and Network Table Entries
        m_sbt_Intake = &frc::Shuffleboard::GetTab(ConShuffleboard::IntakeTab);


        m_nte_MotorCurrent = m_sbt_Intake->AddPersistent("Intake Current", 0.0)
              .WithSize(2,1)
              .WithPosition(0,0)
              .WithWidget(frc::BuiltInWidgets::kDial)
              // Would like to use .WithProperties() to set Max to CURRENT_LIMIT
              .GetEntry();
        m_nte_StowedState = m_sbt_Intake->AddPersistent("Deployed State", true)
              .WithSize(1,1)
              .WithPosition(3,0)
              .GetEntry();
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

void Intake::Periodic() {
  m_nte_MotorCurrent.SetDouble(m_intakeMotor.GetOutputCurrent());
  m_nte_StowedState.SetBoolean(!m_deployedState);
}
