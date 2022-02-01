// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <cmath>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include "commands/AutoTurn.h"

AutoTurn::AutoTurn(DriveTrain *drivetrain) : m_driveTrain(drivetrain) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(drivetrain);
  m_integral = 0;
  // Create and get reference to SB tab
  m_sbt_Robot = &frc::Shuffleboard::GetTab(ConShuffleboard::RobotTab);
  // PID constants: Starting with .5/.001/.3 worked OK on terazzo floor
  m_nte_AutoTurn_kP = m_sbt_Robot->AddPersistent("AutoTurn kP", 0.5).WithSize(1,1).WithPosition(0,1).GetEntry();
  m_nte_AutoTurn_kI = m_sbt_Robot->AddPersistent("AutoTurn kI", 0.001).WithSize(1,1).WithPosition(1,1).GetEntry();
  m_nte_AutoTurn_kD = m_sbt_Robot->AddPersistent("AutoTurn kD", 0.3).WithSize(1,1).WithPosition(2,1).GetEntry();
  m_nte_AutoTurn_error = m_sbt_Robot->AddPersistent("PID Error", 0.0).WithSize(1,1).WithPosition(0,2).GetEntry();
  m_nte_AutoTurn_output = m_sbt_Robot->AddPersistent("PID Output", 0.0).WithSize(1,1).WithPosition(1,2).GetEntry();

}

// Called when the command is initially scheduled.
void AutoTurn::Initialize() {
  m_driveTrain->ResetGyro();
  // Read the target angle from the dashboard
  m_setpoint = m_driveTrain->m_nte_c_DriveTurnAngle.GetDouble(0.0);
  // Read PID control parameters from the dashboard
  m_kP = m_nte_AutoTurn_kP.GetDouble(1.0);
  m_kI = m_nte_AutoTurn_kI.GetDouble(0.0);
  m_kD = m_nte_AutoTurn_kD.GetDouble(0.0);
}

void AutoTurn::PID() {
  double error, derivative;
  error = (m_setpoint - m_driveTrain->GetGyroAngle())/abs(m_setpoint); // Error = Target - Actual, eg 45 degrees, normalized to 0.0 - 1.0
  m_integral += (error*.02); // Integral is increased by the error*time (which is .02 seconds using normal IterativeRobot)
  derivative = (error - m_previous_error) / .02;
  m_output = m_kP * error + m_kI*m_integral + m_kD*derivative;
  m_nte_AutoTurn_error.SetDouble(error);
  m_nte_AutoTurn_output.SetDouble(-m_output);
  m_previous_error = error;
}

// Called repeatedly when this Command is scheduled to run
void AutoTurn::Execute() {

  constexpr double speed = 0.0;

  PID();
  // Negating the output because wheels are rotating in the wrong direction
  m_driveTrain->ArcadeDrive(speed, -m_output);
}

// Called once the command ends or is interrupted.
void AutoTurn::End(bool interrupted) {
  m_driveTrain->ArcadeDrive(0.0, 0.0);  
}

// Returns true when the command should end.
bool AutoTurn::IsFinished() {
  return false;
}
