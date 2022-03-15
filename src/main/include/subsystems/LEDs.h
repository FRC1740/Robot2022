// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#ifdef ENABLE_LED
#include <frc/AddressableLED.h>
#endif // ENABLE_LED

class LEDs : public frc2::SubsystemBase {
 public:
  LEDs();
  void Periodic() override;
  void DisabledInit();
  void DisabledPeriodic();

 private:
#ifdef ENABLE_LED
static constexpr int kLedLength = 100;
static constexpr int kLedPwmPort = 9;
  // Must be a PWM header, not MXP or DIO
  frc::AddressableLED m_led{kLedPwmPort};
  std::array<frc::AddressableLED::LEDData, kLedLength> m_ledBuffer;  // Reuse the buffer

  int m_currentPixel = 0;
  int m_delta = 1;
#endif // ENABLE_LED

};
