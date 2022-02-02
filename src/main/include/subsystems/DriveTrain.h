/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <networktables/NetworkTableEntry.h>
#include <AHRS.h>				 

#include "OI.h"
#include "Constants.h"

namespace ConDriveTrain {
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
    constexpr double WHEEL_DIAMETER = 6.0;
    constexpr double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI; // Abt 19 in.

    constexpr double TICKS_PER_WHEEL_REVOLUTION = ENCODER_TICK_RESOLUTION * GEAR_RATIO; // Abt 450 ticks

    //Conversions
    constexpr double TICKS_PER_INCH = TICKS_PER_WHEEL_REVOLUTION / WHEEL_CIRCUMFERENCE; // Abt 24 ticks per inch
    constexpr double INCHES_PER_TICK = WHEEL_CIRCUMFERENCE / TICKS_PER_WHEEL_REVOLUTION; // Abt 1/24 (.042)

    // degrees to in
    constexpr double ANGLE_2_IN = 25.5*ConMath::PI/360; // FIXME: What is this fudge factor? 25.5?
    constexpr double IN_2_ANGLE= 1/ANGLE_2_IN;
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
  //void SetSafety(bool safety);
  
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  double m_maxOutput = 1.0;
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
