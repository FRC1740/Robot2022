// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/LEDs.h"
#include <frc/DriverStation.h>

LEDs::LEDs() {
#ifdef ENABLE_LED
    m_led.SetLength(kLedLength);
    for (int i = 0; i < kLedLength; i++) {
      m_ledBuffer[i].SetRGB(0, 0, 0);
    }
    m_led.SetData(m_ledBuffer);
    m_led.Start();
#endif // ENABLE_LED
}

void LEDs::Periodic() {
  //double voltage = frc::DriverStation::GetBatteryVoltage();
}

void LEDs::DisabledInit() {
#ifdef ENABLE_LED
  for (int i = 0; i < kLedLength; i++) {
    m_ledBuffer[i].SetRGB(0, 0, 0);
  }
  m_led.SetData(m_ledBuffer);
#endif // ENABLE_LED
}

void LEDs::DisabledPeriodic() {
#ifdef ENABLE_LED
  for (int i = 0; i < kLedLength; i++) {
    int r = m_ledBuffer[i].r;
    int g = m_ledBuffer[i].g;
    int b = m_ledBuffer[i].b;
    if (r >= 10) r -= 10; else r = 0;
    if (g >= 20) g -= 20; else g = 0;
    if (b >= 20) b -= 20; else b = 0;
    m_ledBuffer[i].SetRGB(r, g, b);
  }
  m_ledBuffer[m_currentPixel].SetRGB(255, 255, 255);
  m_currentPixel += m_delta;
  if ((m_currentPixel == 0) || (m_currentPixel == kLedLength - 1)) m_delta = -m_delta;
  m_led.SetData(m_ledBuffer);
#endif // ENABLE_LED
}
