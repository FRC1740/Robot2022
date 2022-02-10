// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ExampleSubsystem.h"

ExampleSubsystem::ExampleSubsystem() {
  // Implementation of subsystem constructor goes here.
  m_relayDirection = frc::Relay::kOff;
}

void ExampleSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
}

void ExampleSubsystem::SimulationPeriodic() {
  // Implementation of subsystem simulation periodic method goes here.
}

void ExampleSubsystem::TestRelay(int direction) {
  if (direction == 1) {
    m_relayDirection = frc::Relay::kForward;
  }
  else {
    m_relayDirection = frc::Relay::kOff;
  }
  testRelay.Set(m_relayDirection);
}

void ExampleSubsystem::TestServo(int direction) {
  if (direction == 1) {
    testServo.Set(1.0);
  }
  else {
    testServo.Set(0.0);
  }

}
