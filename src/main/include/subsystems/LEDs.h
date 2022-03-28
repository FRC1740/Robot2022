// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#ifdef ENABLE_LED
#include <frc/AddressableLED.h>
#endif // ENABLE_LED

namespace ConLED {
  enum mode {
    OFF,
    COLONELS,
    KITT,
    VOLTAGE,
    CLIMBTIME,
  };
}

class LEDs : public frc2::SubsystemBase {
 public:
  LEDs();
  void Periodic() override;
  void Init();
  void On();
  void Off();

 private:
  ConLED::mode m_mode = ConLED::OFF;

#ifdef ENABLE_LED
  int m_delay = 0;
  int m_currentPixel = 0;
  
  void Colonels();
  void Kitt();
  int m_kittDelta = 1;
  void Voltage();
  void ClimbTime();

  static constexpr int kLedLength = 50;
  static constexpr int kLedPwmPort = 9;
  // Must be a PWM header, not MXP or DIO
  frc::AddressableLED m_led{kLedPwmPort};
  std::array<frc::AddressableLED::LEDData, kLedLength> m_ledBuffer;  // Reuse the buffer
#endif // ENABLE_LED

};
