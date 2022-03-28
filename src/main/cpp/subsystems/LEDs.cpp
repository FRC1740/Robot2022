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
#ifdef ENABLE_LED
  if (m_mode != ConLED::OFF) {
    switch (m_mode) {
      case ConLED::COLONELS:
        Colonels();
        break;
      case ConLED::KITT:
        Kitt();
        break;
      default:
        Voltage();
        break;
    }
  }
#endif // ENABLE_LED
}

void LEDs::Init() {
#ifdef ENABLE_LED
  for (int i = 0; i < kLedLength; i++) {
    m_ledBuffer[i].SetRGB(0, 0, 0);
  }
  m_led.SetData(m_ledBuffer);
#endif // ENABLE_LED
}

void LEDs::On() {
  printf("LED::On\n");
  switch (m_mode) {
    case ConLED::COLONELS:
      m_mode = ConLED::KITT;
      break;
    case ConLED::KITT:
      m_mode = ConLED::VOLTAGE;
      break;
    default:
      m_mode = ConLED::COLONELS;
      break;
  }
}

void LEDs::Off() {
  printf("LED::Off\n");
  m_mode = ConLED::OFF;
  Init();
}

#ifdef ENABLE_LED
void LEDs::Colonels() {
  if (--m_delay <= 0) {
    m_delay = 20;

    int colors[][3] = {
      {150/2, 255, 128}, // blue
      {354/2, 255, 128}, // gold
      //{    0,   0,  64}, // white
    };
    int ncolors = sizeof(colors)/sizeof(colors[0]);
    int ix;
    for (int i = 0; i < kLedLength; i++) {
      ix = (m_currentPixel + i) % ncolors;
      m_ledBuffer[i].SetHSV(colors[ix][0], colors[ix][1], colors[ix][2]);
    }
    m_led.SetData(m_ledBuffer);
    m_currentPixel = (m_currentPixel + 1) % kLedLength;
  }
}

void LEDs::Kitt() {
  if (--m_delay <= 0) {
    m_delay = 1;

    for (int i = 0; i < kLedLength; i++) {
      int r = m_ledBuffer[i].r;
      int g = m_ledBuffer[i].g;
      int b = m_ledBuffer[i].b;
      if (r >= 10) r -= 10; else r = 0;
      if (g >= 20) g -= 20; else g = 0;
      if (b >= 20) b -= 20; else b = 0;
      m_ledBuffer[i].SetRGB(r, g, b);
    }
    m_ledBuffer[m_currentPixel].SetRGB(64,64,64);
    m_led.SetData(m_ledBuffer);

    m_currentPixel += m_kittDelta;
    if ((m_currentPixel <= 0) || (m_currentPixel >= kLedLength - 1)) {
      // Ensure valid even when switching modes
      if (m_currentPixel < 0) m_currentPixel = 0;
      if (m_currentPixel > kLedLength - 1) m_currentPixel = kLedLength - 1;
      m_kittDelta = -m_kittDelta;
    }
  }
}

void LEDs::Voltage() {
  if (--m_delay <= 0) {
    m_delay = 30;
    double voltage = frc::DriverStation::GetBatteryVoltage();
    constexpr double vmin = 9;
    constexpr double vmax = 12.5;
    int meter = (int) ((voltage - vmin) / (vmax - vmin) * (double) kLedLength);
    if (meter > kLedLength - 1) meter = kLedLength - 1;
    if (meter < 0) meter = 0;
    //printf("voltage %f meter %d\n", voltage, meter);

    for (int i = 0; i < kLedLength; i++) {
      if (i <= meter) {
        m_ledBuffer[i].SetRGB(0, 0, 128);
      } else {
        m_ledBuffer[i].SetRGB(0, 0, 0);
      }
    }
    m_led.SetData(m_ledBuffer);
  }
}

#endif // ENABLE_LED
