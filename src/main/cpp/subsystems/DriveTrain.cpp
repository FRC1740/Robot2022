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

  m_leftEncoderA.SetPositionConversionFactor(ConDriveTrain::ENCODER_2_IN);
  m_rightEncoderA.SetPositionConversionFactor(ConDriveTrain::ENCODER_2_IN);

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
  m_nte_a_DriveDelay        = m_sbt_DriveTrain->AddPersistent("a Drive Delay", 0.0)         .WithSize(1, 1).WithPosition(1, 0).GetEntry();
  m_nte_b_DriveDistance     = m_sbt_DriveTrain->AddPersistent("b Drive Distance", -20.0)    .WithSize(1, 1).WithPosition(1, 1).GetEntry();
  m_nte_c_ShooterSpinTime   = m_sbt_DriveTrain->AddPersistent("c Shooter Spin Time", 10.0)  .WithSize(1, 1).WithPosition(1, 2).GetEntry();
  m_nte_d_JumblerDelay      = m_sbt_DriveTrain->AddPersistent("d Jumbler Delay ", 5.0)      .WithSize(1, 1).WithPosition(1, 3).GetEntry();
  m_nte_e_JumblerOnTime     = m_sbt_DriveTrain->AddPersistent("e Jumbler On Time", 15.0)    .WithSize(1, 1).WithPosition(1, 4).GetEntry();
}

#ifdef ENABLE_DRIVETRAIN
// This method will be called once per scheduler run
//void DriveTrain::Periodic() {}

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

// FIXME: Account for two encoders per side
double DriveTrain::GetRightDistance() {
  return (m_rightEncoderA.GetPosition() * ConDriveTrain::ENCODER_2_IN);
}

double DriveTrain::GetLeftDistance() {
  return (m_leftEncoderA.GetPosition() * ConDriveTrain::ENCODER_2_IN);
}

// Used by AutoDriveDistance
double DriveTrain::GetAverageEncoderDistance() {
  // return (m_leftEncoderA.GetPosition() - m_rightEncoderA.GetPosition()) / 2.0;
  return ((GetLeftDistance() - GetRightDistance()) / 2.0)/ 13.16; // FIXME: Fudge Factor 
}

void DriveTrain::GoToAngle(double angle) {
  angle *= ConDriveTrain::ANGLE_2_IN;
// The following syntax is deprecated in 2022 and throws a warning error
//left_pidController.SetReference(angle, rev::ControlType::kSmartMotion);
//right_pidController.SetReference(angle, rev::ControlType::kSmartMotion);
//left_pidController.SetReference(angle, CANSparkMax::ControlType::kSmartMotion);
//right_pidController.SetReference(angle, CANSparkMax::ControlType::kSmartMotion);

}

double DriveTrain::GetGyroAngle() {return gyro->GetAngle();}
																	   
void DriveTrain::ResetGyro() {gyro->Reset();}												
																				 
// void DriveTrain::SetSafety(bool safety) { SetSafetyEnabled(safety);}

#endif // ENABLE_DRIVETRAIN
