// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>

#include "Constants.h"

//#include "commands/ExampleCommand.h"
//#include "subsystems/ExampleSubsystem.h"
#include "commands/TeleOpDrive.h"
#include "commands/AutoDrive.h"
#include "subsystems/DriveTrain.h"
#include "subsystems/Shooter.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();
  frc2::Command* GetDisabledCommand();
  
  // The driver's game controller
  frc::XboxController driver_control{ConXBOXControl::DRIVER_CONTROLLER_PORT};
  // The codriver's game controller
  //frc::XboxController codriver_control{ConLaunchPad::LAUNCHPAD_CONTROLLER_PORT};

 private:
  // The robot's subsystems and commands are defined here...
  // Subsystems
  DriveTrain m_driveTrain;
  Shooter m_shooter;
  
  // Commands...
  AutoDrive m_autoDrive;
  
  //ExampleSubsystem m_subsystem;
  //ExampleCommand m_autonomousCommand;

  void ConfigureButtonBindings();
};