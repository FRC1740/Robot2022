// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrain.h"
/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoTurn
    : public frc2::CommandHelper<frc2::CommandBase, AutoTurn> {
 public:
  AutoTurn(DriveTrain *drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  void PID();

 private:

  DriveTrain *m_driveTrain;
  frc::ShuffleboardTab* m_sbt_Robot;
  nt::NetworkTableEntry m_nte_AutoTurn_kP;
  nt::NetworkTableEntry m_nte_AutoTurn_kI;
  nt::NetworkTableEntry m_nte_AutoTurn_kD;
  nt::NetworkTableEntry m_nte_AutoTurn_error;
  nt::NetworkTableEntry m_nte_AutoTurn_output;
  double m_angle_degrees;
  double m_rotationOut = 0.0;
  double m_kP, m_kI, m_kD, m_setpoint, m_integral, m_output, m_previous_error;


};
