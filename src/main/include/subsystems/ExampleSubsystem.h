// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Servo.h>
#include <frc/Relay.h>

// Define a namespace for each subsystems constants...
namespace ConExample {
  constexpr int RELAY_PORT=0; // RoboRio RELAY port number
  constexpr int SERVO_PORT=2; // RoboRio PWM port number
}
class ExampleSubsystem : public frc2::SubsystemBase {
 public:
  ExampleSubsystem();
  void TestRelay(int);
  void TestServo(int);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Will be called periodically whenever the CommandScheduler runs during
   * simulation.
   */
  void SimulationPeriodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  frc::Relay testRelay {ConExample::RELAY_PORT};
  frc::Relay::Value m_relayDirection;
  frc::Servo testServo {ConExample::SERVO_PORT};

};
