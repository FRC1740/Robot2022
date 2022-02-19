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

        // Initialize Shuffleboard Tab and Network Table Entries
        m_sbt_Intake = &frc::Shuffleboard::GetTab(ConShuffleboard::IntakeTab);

        m_nte_MotorPower = m_sbt_Intake->AddPersistent("Motor Power", ConIntake::INTAKE_POWER)
              .WithSize(2,1)
              .WithPosition(0,0)
              .GetEntry();
        m_nte_ShutdownDelay = m_sbt_Intake->AddPersistent("Shutdown Delay", (double)ConIntake::SHUTDOWN_DELAY)
              .WithSize(2,1)
              .WithPosition(0,1)
              .GetEntry();
        m_nte_MotorCurrent = m_sbt_Intake->AddPersistent("Intake Current", 0.0)
              .WithSize(2,1)
              .WithPosition(0,2)
              .WithWidget(frc::BuiltInWidgets::kDial)
              // .WithProperties({"min" : 0, "max" : ConIntake::CURRENT_STALL_LIMIT});
              // Would like to use .WithProperties() to set Max to CURRENT_LIMIT
              .GetEntry();

        m_nte_StowedState = m_sbt_Intake->AddPersistent("Deployed State", true)
              .WithSize(2,2)
              .WithPosition(2,0)
              .GetEntry();


        m_timer = frc::Timer(); // For delayed shutdown of intake motor
        }

void Intake::ToggleDeployedState() {
  m_deployedState == true ? Stow() : Deploy();
}

void Intake::Deploy() {
  printf("Intake::Deploy() Executing...\n");
  deployDoublePCM.Set(frc::DoubleSolenoid::Value::kForward);
  m_deployedState = true;
  Load();
}

void Intake::Stow() {
  printf("Intake::Stow() Executing...\n");
  
  deployDoublePCM.Set(frc::DoubleSolenoid::Value::kReverse);
  m_timer.Reset();
  m_timer.Start();
  m_deployedState = false;
}

void Intake::Load() {
  printf("Intake::Load() Executing...\n");
  if (m_deployedState) {
    m_intakeMotor.Set(ConIntake::LOAD_BALL * m_intakePower);
  } else {
    m_intakeMotor.Set(0.0);
  }
}

void Intake::Reject() {
  printf("Intake::Reject() Executing...\n");
  if (m_deployedState) {
    m_intakeMotor.Set(ConIntake::REJECT_BALL * m_intakePower);
  } else {
    m_intakeMotor.Set(0.0);
  }  
}

void Intake::Periodic() {
  m_nte_MotorCurrent.SetDouble(m_intakeMotor.GetOutputCurrent());
  m_nte_StowedState.SetBoolean(!m_deployedState);
  m_intakePower = m_nte_MotorPower.GetDouble(ConIntake::INTAKE_POWER);
  if (m_deployedState == false && m_timer.Get() > ConIntake::SHUTDOWN_DELAY) {
    m_intakeMotor.Set(0.0);
  }
}
