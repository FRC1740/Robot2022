// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/PIDSubsystem.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Relay.h>

class Intake : public frc2::PIDSubsystem {
 public:
  Intake();
  void Deploy();
  void Retract();
  void Inject();
  void Reject();
  void TestRelay(int);

 protected:
  void UseOutput(double output, double setpoint) override;

  double GetMeasurement() override;

  frc::DoubleSolenoid deployDoublePCM{frc::PneumaticsModuleType::CTREPCM, 0, 1};
  frc::Relay testRelay {0};
  frc::Relay::Value m_relayDirection;
};
