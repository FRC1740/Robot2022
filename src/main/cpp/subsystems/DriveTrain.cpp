/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"

DriveTrain::DriveTrain() {
#ifdef ENABLE_DRIVETRAIN
  // Settings for Spark Max motor controllers should be done here, in code
  // and not in the Spark Max Client Software
  m_rightMotorA.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);
  m_rightMotorB.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);
  m_leftMotorA.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);
  m_leftMotorB.SetOpenLoopRampRate(ConDriveTrain::RAMP_RATE);

  /* 
    To swap front & back of robot, swap the INVERTED/NONINVERTED below and add or remove the minus sign 
    in RobotContainer.cpp on the line which contains "ConXBOXControl::LEFT_JOYSTICK_X/4" for the turning axis
  */
  // WARNING! TuffBox Mini requires BOTH motors spin in the same direction!!!
  m_rightMotorA.SetInverted(ConDriveTrain::NONINVERTED);
  m_rightMotorB.SetInverted(ConDriveTrain::NONINVERTED);
  // WARNING! TuffBox Mini requires BOTH motors spin in the same direction!!!
  m_leftMotorA.SetInverted(ConDriveTrain::INVERTED);
  m_leftMotorB.SetInverted(ConDriveTrain::INVERTED);

  // set PID coefficients
  // left pid controller
  left_pidController.SetP(kP);
  left_pidController.SetI(kI);
  left_pidController.SetD(kD);
  left_pidController.SetIZone(kIz);
  left_pidController.SetFF(kFF);
  left_pidController.SetOutputRange(kMinOutput, kMaxOutput);

  // right pid controller
  right_pidController.SetP(kP);
  right_pidController.SetI(kI);
  right_pidController.SetD(kD);
  right_pidController.SetIZone(kIz);
  right_pidController.SetFF(kFF);
  right_pidController.SetOutputRange(kMinOutput, kMaxOutput);

  /**
   * Smart Motion coefficients are set on a SparkMaxPIDController  object
   * 
   * - SetSmartMotionMaxVelocity() will limit the velocity in RPM of
   * the pid controller in Smart Motion mode
   * - SetSmartMotionMinOutputVelocity() will put a lower bound in
   * RPM of the pid controller in Smart Motion mode
   * - SetSmartMotionMaxAccel() will limit the acceleration in RPM^2
   * of the pid controller in Smart Motion mode
   * - SetSmartMotionAllowedClosedLoopError() will set the max allowed
   * error for the pid controller in Smart Motion mode
   */
  // left pid controller
  left_pidController.SetSmartMotionMaxVelocity(kMaxVel);
  left_pidController.SetSmartMotionMinOutputVelocity(kMinVel);
  left_pidController.SetSmartMotionMaxAccel(kMaxAcc);
  left_pidController.SetSmartMotionAllowedClosedLoopError(kAllErr);

  //right pid controller
  right_pidController.SetSmartMotionMaxVelocity(kMaxVel);
  right_pidController.SetSmartMotionMinOutputVelocity(kMinVel);
  right_pidController.SetSmartMotionMaxAccel(kMaxAcc);
  right_pidController.SetSmartMotionAllowedClosedLoopError(kAllErr);

  // Set additional motor controllers on drive train to follow
  m_rightMotorB.Follow(m_rightMotorA, false);
  m_leftMotorB.Follow(m_leftMotorA, false);

  // NavX gyro
  gyro = new AHRS(frc::SPI::Port::kMXP);

  /*
     FIXME: This may be a better way to set the distance conversion: Right on the SparkMax!
     Native Tick counts * Gear Ratio divided by Wheel circumference (42 * 10.71)/(6 * pi) = ticks per inch
     We can use the SetPositionConversionFactor() to use this as our tick reference.
     // m_leftEncoderA.SetPositionConversionFactor(ConDriveTrain::TICKS_PER_INCH);
     // m_rightEncoderA.SetPositionConversionFactor(ConDriveTrain::TICKS_PER_INCH);
     // m_leftEncoderB.SetPositionConversionFactor(ConDriveTrain::TICKS_PER_INCH);
     // m_rightEncoderB.SetPositionConversionFactor(ConDriveTrain::TICKS_PER_INCH);
    BUUUT: IF YOU DO THIS, CHANGE THE GetLeftDistanceInches() and GetRightDistanceInches() methods!!!

  */

  // Save all SparkMax firmware parameters to flash memory
  m_leftMotorA.BurnFlash();
  m_leftMotorB.BurnFlash();
  m_rightMotorA.BurnFlash();
  m_rightMotorB.BurnFlash();

#endif // ENABLE_DRIVETRAIN

  // Create and get reference to SB tab
  m_sbt_DriveTrain = &frc::Shuffleboard::GetTab(ConShuffleboard::DriveTrainTab);

  // Create widgets for digital filter lengths
  m_nte_DriveSpeedFilter    = m_sbt_DriveTrain->AddPersistent("Drive Speed Filter", 10.0)   .WithSize(2, 1).WithPosition(0, 0).GetEntry();
  m_nte_DriveRotationFilter = m_sbt_DriveTrain->AddPersistent("Drive Rotation Filter", 5.0) .WithSize(2, 1).WithPosition(0, 1).GetEntry();

  // Create widget for non-linear input
  m_nte_InputExponent       = m_sbt_DriveTrain->AddPersistent("Input Exponent", 1.0)        .WithSize(1, 1).WithPosition(0, 2).GetEntry();

  // Create widgets for AutoDrive
  m_nte_a_DriveDelay        = m_sbt_DriveTrain->AddPersistent("a Drive Delay", 0.0)         .WithSize(1, 1).WithPosition(3, 0).GetEntry();
  m_nte_b_DriveDistance     = m_sbt_DriveTrain->AddPersistent("b Drive Distance", 0.0)    .WithSize(1, 1).WithPosition(3, 1).GetEntry();
  m_nte_c_DriveTurnAngle     = m_sbt_DriveTrain->AddPersistent("c Turn Angle", 0.0)       .WithSize(1, 1).WithPosition(3, 2).GetEntry();
  //  m_nte_Testing     = m_sbt_DriveTrain->AddPersistent("Testing", 0.0)       .WithSize(1, 1).WithPosition(3, 3).GetEntry();

  // Display current encoder values
  m_nte_LeftEncoder = m_sbt_DriveTrain->AddPersistent("Left Side Encoder", 0.0)             .WithSize(2,1).WithPosition(4,0).GetEntry();
  m_nte_RightEncoder = m_sbt_DriveTrain->AddPersistent("Right Side Encoder", 0.0)            .WithSize(2,1).WithPosition(4,1).GetEntry();
  m_nte_IMU_ZAngle = m_sbt_DriveTrain->AddPersistent("IMU Z-Axis Angle", 0.0)               .WithSize(2,1).WithPosition(4,2).GetEntry();

  // End of DriveTrain Constructor
  printf("DriveTrain() Constructor returning...\n");
}

#ifdef ENABLE_DRIVETRAIN
// This method will be called once per scheduler run
void DriveTrain::Periodic() {
  m_nte_LeftEncoder.SetDouble(GetAverageLeftEncoders());
  m_nte_RightEncoder.SetDouble(GetAverageRightEncoders());
  m_nte_IMU_ZAngle.SetDouble(GetGyroAngle());
}

// Used by TeleOpDrive
void DriveTrain::ArcadeDrive(double speed, double rotation) {
  m_driveTrain.ArcadeDrive(speed, DeadZone(rotation));
}

// Used by AlignToPlayerStationPID
void DriveTrain::TankDrive(double left, double right){
  m_driveTrain.TankDrive(left, right);
}

// Used by TeleOpSlowDrive
double DriveTrain::GetMaxOutput() {
    return m_maxOutput;
}
// Why is this method recursive?
void DriveTrain::SetMaxOutput(double maxOutput) {
  m_maxOutput = maxOutput;
  m_driveTrain.SetMaxOutput(maxOutput);
}

// Used by AutoDriveDistance
void DriveTrain::ResetEncoders() {
  m_rightEncoderA.SetPosition(0.0);
  m_rightEncoderB.SetPosition(0.0);
  m_leftEncoderA.SetPosition(0.0);
  m_leftEncoderB.SetPosition(0.0);
}

// Account for two encoders per side
double DriveTrain::GetRightDistanceInches() {
  return (GetAverageRightEncoders() * ConDriveTrain::INCHES_PER_TICK);
}

double DriveTrain::GetLeftDistanceInches() {
  return (GetAverageLeftEncoders() * ConDriveTrain::INCHES_PER_TICK);
}

// Used by AutoDriveDistance
double DriveTrain::GetAverageDistanceInches() {
  // FIXME: Should't these be added, or is one negative? I think we just REVERSE the encoder. CRE 2022-01-25
  return ((GetLeftDistanceInches() + GetRightDistanceInches()) / 2.0);
}

double DriveTrain::GetAverageLeftEncoders() {
  return (m_leftEncoderA.GetPosition() + m_leftEncoderB.GetPosition() ) / 2.0;
}

double DriveTrain::GetAverageRightEncoders() {
  return (m_rightEncoderA.GetPosition() + m_rightEncoderB.GetPosition() ) / 2.0;
}
void DriveTrain::GoToAngle(double angle) {
  angle *= ConDriveTrain::ANGLE_2_IN;
  // FIXME: The following syntax is deprecated in 2022 and throws a warning error, but the recommended
  // fix throws a compiler/unknown reference error for CANSparkMax::ControlType
  //  Use SetReference(double, CANSparkMax::ControlType, int, double, SparkMaxPIDController::ArbFFUnits) instead [-Wdeprecated-declarations]
  //  right_pidController.SetReference(angle, rev::ControlType::kSmartMotion);
  left_pidController.SetReference(angle, rev::ControlType::kSmartMotion);
  right_pidController.SetReference(angle, rev::ControlType::kSmartMotion);
}

double DriveTrain::GetGyroAngle() {return gyro->GetAngle();}

// Used by AutoTurn 																	   
void DriveTrain::ResetGyro() {
  gyro->Reset();
}																				 
// void DriveTrain::SetSafety(bool safety) { SetSafetyEnabled(safety);}

#endif // ENABLE_DRIVETRAIN
