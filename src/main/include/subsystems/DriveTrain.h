/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include <AHRS.h>

#include "OI.h"
#include "Constants.h"

namespace ConDriveTrain {
    // Autonomous Constants
    constexpr double AUTONOMOUS_DISTANCE = 84;  // 84.75 inches Needed to exit the launchpad 
    constexpr double AUTONOMOUS_DRIVE_DELAY = 5.0; // Seconds to delay between launch & drive
    constexpr int AUTONOMOUS_MODE_2_BALL = 1;
    constexpr int AUTONOMOUS_MODE_LAUNCH_DELAY_MOVE = 2;
    constexpr int AUTONOMOUS_MODE_JUST_MOVE = 3;
    constexpr int AUTONOMOUS_MODE_5_BALL = 5;

    // Motors
    constexpr int RIGHT_MOTOR_A_ID = 2;
    constexpr int RIGHT_MOTOR_B_ID = 4;
    constexpr int LEFT_MOTOR_A_ID = 3;
    constexpr int LEFT_MOTOR_B_ID = 5;
    //constexpr double ROTATION_FACTOR = 1/1.3;

    //Spark Max Settings
    constexpr int RAMP_RATE = 0.100; //seconds
    constexpr bool INVERTED = true; //
    constexpr bool NONINVERTED = false; //
    
    // Neo Motor & Gearbox
    constexpr double ENCODER_TICK_RESOLUTION = 42.0; // IS IT REALLY 42? or 48? or maybe 24?  
    constexpr double GEAR_RATIO = 10.71; // Neo rotates 10.71 times for one rotation of the output
    constexpr units::length::inch_t WHEEL_DIAMETER = 6.0_in;
    constexpr units::length::inch_t WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI; // Abt 18.85 in.

    constexpr double TICKS_PER_WHEEL_REVOLUTION = ENCODER_TICK_RESOLUTION * GEAR_RATIO; // Abt 450 ticks

    //Conversions
    constexpr double TICKS_PER_INCH = TICKS_PER_WHEEL_REVOLUTION / (double)WHEEL_CIRCUMFERENCE; // Abt 24 ticks per inch
    constexpr double INCHES_PER_TICK = (double)WHEEL_CIRCUMFERENCE / TICKS_PER_WHEEL_REVOLUTION; // Abt 1/24 (.042)

    // degrees to in
    constexpr double ANGLE_2_IN = 25.5*ConMath::PI/360; // FIXME: What is this fudge factor? 25.5?
    constexpr double IN_2_ANGLE= 1/ANGLE_2_IN;

    // Experimental Drive Characterization/SysID for Trajectory Following
    // These are example values only - DO NOT USE THESE FOR YOUR OWN ROBOT!
    // These characterization values MUST be determined either experimentally or
    // theoretically for *your* robot's drive. The Robot Characterization
    // Toolsuite provides a convenient tool for obtaining these values for your
    // robot.
    constexpr auto ks = 0.14251_V;
    constexpr auto kv = 1.98 * 1_V * 1_s / 1_in;
    constexpr auto ka = 0.2 * 1_V * 1_s * 1_s / 1_in;

    // Example value only - as above, this must be tuned for your drive!
    constexpr double kPDriveVel = 0.14047;

    constexpr auto kTrackwidth = 22.8125_in;
    extern const frc::DifferentialDriveKinematics kDriveKinematics;
    constexpr auto kMaxSpeed = 3_mps;
    constexpr auto kMaxAcceleration = 3_mps_sq;

    // Reasonable baseline values for a RAMSETE follower in units of meters and
    // seconds
    constexpr double kRamseteB = 39.3701 * 2.0; // Inches. Was: 2;
    constexpr double kRamseteZeta = 0.7;
}

class DriveTrain : public frc2::SubsystemBase {
 public:
 
  DriveTrain();
  frc::ShuffleboardTab *m_sbt_DriveTrain;
  nt::NetworkTableEntry m_nte_DriveSpeedFilter;
  nt::NetworkTableEntry m_nte_DriveRotationFilter;
  nt::NetworkTableEntry m_nte_InputExponent;

  // Encoder outputs
  nt::NetworkTableEntry m_nte_LeftEncoder;
  nt::NetworkTableEntry m_nte_RightEncoder;
  nt::NetworkTableEntry m_nte_IMU_ZAngle;

  nt::NetworkTableEntry m_nte_Testing;

  // Autonomous Variables
  nt::NetworkTableEntry m_nte_a_DriveDelay;
  nt::NetworkTableEntry m_nte_b_DriveDistance;
  nt::NetworkTableEntry m_nte_c_DriveTurnAngle;
  nt::NetworkTableEntry m_nte_autoDriveMode;
  
#ifdef ENABLE_DRIVETRAIN
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  /**
   * Drives the robot using arcade controls.
   *
   * @param speed the commanded forward movement
   * @param rotation the commanded rotation
   */
  void ArcadeDrive(double speed, double rotation);

  void TankDrive(double left, double right);

  double GetMaxOutput();

  void SetMaxOutput(double maxOutput);

  double GetRightDistanceInches();
  double GetLeftDistanceInches();
  double GetAverageDistanceInches();
  
  double GetAverageRightEncoders();
  double GetAverageLeftEncoders();

  double GetGyroAngle();
  void ResetEncoders();

  void GoToAngle(double angle);
  void ResetGyro();
#endif // ENABLE_DRIVETRAIN

  // Retrieve from dashboard, set member variables
  void SetAutonomousParameters();

  void BurnFlash();
  //void SetSafety(bool safety);
  
  // Autonomous drive parameters
  double m_autoDistance = ConDriveTrain::AUTONOMOUS_DISTANCE;
  double m_autoDriveMode = ConDriveTrain::AUTONOMOUS_MODE_2_BALL;
  double m_autoDriveDelay = ConDriveTrain::AUTONOMOUS_DRIVE_DELAY;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  double m_maxOutput = 1.0;

#ifdef ENABLE_DRIVETRAIN
  AHRS *gyro;

  // Neo motor controllers
  rev::CANSparkMax m_rightMotorA{ConDriveTrain::RIGHT_MOTOR_A_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_rightMotorB{ConDriveTrain::RIGHT_MOTOR_B_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorA{ConDriveTrain::LEFT_MOTOR_A_ID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_leftMotorB{ConDriveTrain::LEFT_MOTOR_B_ID, rev::CANSparkMax::MotorType::kBrushless};

  /* Drive Train Smart Motion PID set-up below */
  rev::SparkMaxPIDController  left_pidController = m_leftMotorA.GetPIDController();
  rev::SparkMaxPIDController  right_pidController = m_rightMotorA.GetPIDController();

  // default PID coefficients
  double kP = 5e-5, kI = 1e-6, kD = 0, kIz = 0, kFF = 0.000156, kMaxOutput = 1, kMinOutput = -1;

  // default smart motion coefficients
  double kMaxVel = 2000, kMinVel = 0, kMaxAcc = 1500, kAllErr = 0;

  // motor max RPM
  const double MaxRPM = 5700;

  // Drive encoders
  rev::SparkMaxRelativeEncoder m_rightEncoderA = m_rightMotorA.GetEncoder();
  rev::SparkMaxRelativeEncoder m_rightEncoderB = m_rightMotorB.GetEncoder();
  rev::SparkMaxRelativeEncoder m_leftEncoderA = m_leftMotorA.GetEncoder();
  rev::SparkMaxRelativeEncoder m_leftEncoderB = m_leftMotorB.GetEncoder();

  // Robot Drive
  frc::DifferentialDrive m_driveTrain{m_leftMotorA, m_rightMotorA};
#endif // ENABLE_DRIVETRAIN
};
