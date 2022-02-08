# Robot2022

## FIRST Robotics FRC 2022 Command Based Robot

C++/WPILib control system code for 2022 competition season

### Subsystems
- DriveTrain (4xSparkMax)
- Launcher (2xSparkMax)
- Intake (1xSparkMax; 1xDoubleSolenoid)
- Climber (1xSparkMax)

### Commands
- TeleopDrive
- Launch: Launch 1 or 2 balls from catapult
- Deploy: Deploy Intake outside robot perimiter for retrieving balls
- Stow: Stow Intake back within robot perimeter

### Autonomous Commands
- AutoDriveDistance
- AutoTurn
- AutoDelay

### Autonomous Command Groups
- AutoDrive
