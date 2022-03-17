/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vision.h"
#include "OI.h"

Vision::Vision() {
    m_nt_Limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    m_sbt_Vision = &frc::Shuffleboard::GetTab(ConShuffleboard::VisionTab);
    m_nte_Align_P = m_sbt_Vision->AddPersistent("Vision P", 1.0)  .WithSize(1, 1).WithPosition(0, 0).GetEntry();;
    m_nte_Align_I = m_sbt_Vision->AddPersistent("Vision I", 0.0)  .WithSize(1, 1).WithPosition(0, 1).GetEntry();;
    m_nte_Align_D = m_sbt_Vision->AddPersistent("Vision D", 100.0).WithSize(1, 1).WithPosition(0, 2).GetEntry();;

#ifdef ENABLE_VISION
    // If using Vision Tracking use the following:
    // LightOn();
    // m_nt_Limelight->PutNumber("camMode", ConVision::VISION_TRACKING);
    LightOff();
    m_nt_Limelight->PutNumber("camMode", ConVision::DRIVER_ONLY);
#endif
}

#ifdef ENABLE_VISION
void Vision::InitVision() {
    LightOff();
    m_nt_Limelight->PutNumber("camMode", ConVision::DRIVER_ONLY);    
}
// This method will be called once per scheduler run
void Vision::Periodic() {}

double Vision::Align() {
    m_nte_tx = m_nt_Limelight->GetNumber("tx", 0.0);
    return m_nte_tx;
}

void Vision::ToggleLight() {
    if (m_nt_Limelight->GetNumber("ledMode", ConVision::ON) == ConVision::OFF) {
        m_nt_Limelight->PutNumber("ledMode", ConVision::ON);
    } 
    else {
        m_nt_Limelight->PutNumber("ledMode", ConVision::OFF);
    }
}

void Vision::LightOn() {
    m_nt_Limelight->PutNumber("ledMode", ConVision::ON);
}

void Vision::LightOff() {
    m_nt_Limelight->PutNumber("ledMode", ConVision::OFF);
}

void Vision::SelectPlayerStationPipeline() {
    m_nt_Limelight->PutNumber("pipeline", 0);
}

void Vision::SelectNearGoalPipeline() {
    m_nt_Limelight->PutNumber("pipeline", 1);
}

void Vision::SelectFarGoalPipeline() {
    m_nt_Limelight->PutNumber("pipeline", 2);
}
#endif // ENABLE_VISION
