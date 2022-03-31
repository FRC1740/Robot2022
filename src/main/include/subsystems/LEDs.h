// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#ifdef ENABLE_LED
#include <frc/DriverStation.h>
#include <frc/AddressableLED.h>
#endif // ENABLE_LED

namespace ConLED {
  enum mode {
    OFF,
    COLONELS,
    KITT,
    VOLTAGE,
    CLIMBTIME,
    DISABLED,
    AUTONOMOUS,
    TELEOP,
  };
}

class LEDs : public frc2::SubsystemBase {
 public:
  LEDs();
  void Periodic() override;
  void Init();
  void On();
  void Off();
  void SetMode(ConLED::mode newMode);

 private:
  ConLED::mode m_mode = ConLED::OFF;

#ifdef ENABLE_LED
  int m_delay = 0;
  int m_currentPixel = 0;
  int m_blink = 1;
  void Colonels(); // Blue & White
  void Kitt(); // Cylon
  int m_kittDelta = 1;
  void Voltage();
  void Teleop();   // Blue or Red depending on alliance
  void Disabled(); // RSL Orange
  void ClimbTime(); // Flashing Green

  frc::DriverStation::Alliance m_alliance;
  static constexpr int kLedLength = 13;
  static constexpr int kLedAPwmPort = 7;
  static constexpr int kLedBPwmPort = 9;
  // Must be a PWM header, not MXP or DIO
  frc::AddressableLED m_ledA{kLedAPwmPort};
  //frc::AddressableLED m_ledB{kLedBPwmPort};
  // Both LED strips MUST Be the same length
  std::array<frc::AddressableLED::LEDData, kLedLength> m_ledBuffer;  // Reuse the buffer
#endif // ENABLE_LED

};
