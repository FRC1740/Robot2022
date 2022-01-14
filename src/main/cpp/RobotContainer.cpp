// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_autoDrive(&m_driveTrain, &m_shooter) {
  // ANOTHER WAY OF CONSTRUCTING: m_autoDriveDistance = AutoDriveDistance(&m_driveTrain);
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

#ifdef ENABLE_DRIVETRAIN
// #define ENABLE_FLIGHTSTICK
#ifdef ENABLE_FLIGHTSTICK
  // Set up default drive command
  m_driveTrain.SetDefaultCommand(TeleOpDrive(
    &m_driveTrain,
    [this] { return driver_control.GetRawAxis(ConFlightControl::ELEVATOR); },
    [this] { return driver_control.GetRawAxis(ConFlightControl::RUDDER); }));

#endif
#ifndef ENABLE_FLIGHTSTICK
  // Set up default drive command
  m_driveTrain.SetDefaultCommand(TeleOpDrive(
    &m_driveTrain,
    [this] { return driver_control.GetRawAxis(ConXBOXControl::RIGHT_TRIGGER) - driver_control.GetRawAxis(ConXBOXControl::LEFT_TRIGGER); },
    // Scale turning by a 25% for at-home challenges  
    [this] { return driver_control.GetRawAxis(ConXBOXControl::LEFT_JOYSTICK_X/4); }));
#endif
#endif // ENABLE_DRIVETRAIN

}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autoDrive;
}
