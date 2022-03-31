// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/LEDs.h"
#include <frc/DriverStation.h>

LEDs::LEDs() {
#ifdef ENABLE_LED
  m_ledA.SetLength(kLedLength);
  // m_ledB.SetLength(kLedLength);
  for (int i = 0; i < kLedLength; i++) {
    m_ledBuffer[i].SetRGB(0, 0, 0);
  }
  m_ledA.SetData(m_ledBuffer);
  m_ledA.Start();
  // m_ledB.SetData(m_ledBuffer);
  // m_ledB.Start();

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
      case ConLED::AUTONOMOUS:
        Kitt();
        break;
      case ConLED::VOLTAGE:
        Voltage();
        break;
      case ConLED::TELEOP:
        if (frc::DriverStation::GetMatchTime() >= ConLED::TIME_TO_CLIMB) {
          Teleop();
        } else {
          ClimbTime();
        }
        break;
      case ConLED::DISABLED:
        Disabled();
        break;
      default:
        ClimbTime();
        break;
    }
  }
#endif // ENABLE_LED
}

void LEDs::Init() {
#ifdef ENABLE_LED
  m_alliance = frc::DriverStation::GetAlliance();

  for (int i = 0; i < kLedLength; i++) {
    m_ledBuffer[i].SetRGB(0, 0, 0);
  }
  m_ledA.SetData(m_ledBuffer);
  // m_ledB.SetData(m_ledBuffer);

#endif // ENABLE_LED
}

void LEDs::On() {
  printf("LED::On\n");
  switch (m_mode) {
    case ConLED::COLONELS:
      Colonels();
      break;
    case ConLED::KITT:
    case ConLED::AUTONOMOUS:
      Kitt();
      break;
    case ConLED::VOLTAGE:
      Voltage();
      break;
    case ConLED::TELEOP:
      Teleop();
      break;
    case ConLED::DISABLED:
      Disabled();
      break;
    default:
      ClimbTime();
      break;
  }
}
void LEDs::SetMode(ConLED::mode newMode) {
  m_mode = newMode;
} 

void LEDs::Off() {
  printf("LED::Off\n");
  m_mode = ConLED::OFF;
  Init();
}

/*
 * Add helper macros because the LEDs we use have the B and G channels swapped.
 * Instead of setting (R,G,B) the AddressableLED interface actually sets (R,B,G)
 * And, for the same reason the Hue channel of HSV goes around the circle counterclockwise
 * Reference: https://en.wikipedia.org/wiki/HSL_and_HSV
 * Let's change the API (only for code below) to something more intuitive
 */

#define SetTrue_R_G_B(_r,_g,_b) SetRGB(_r, _b, _g)
#define SetTrue_H360_S_V(_h,_s,_v) SetHSV((360-(_h))/2,_s,_v)  // A full 0-360 hue
#define GetR r
#define GetG b
#define GetB g
#define TurnOff SetRGB(0,0,0)

#ifdef ENABLE_LED
void LEDs::Colonels() {
  if (--m_delay <= 0) {
    m_delay = 20;

    int colors[][3] = {
      {210, 255, 128}, // blue
      {210, 255, 128}, // blue
      {210, 255, 128}, // blue
      {  0,   0,  64}, // white
      //{  6, 255, 128}, // gold
    };
    int ncolors = sizeof(colors)/sizeof(colors[0]);
    int ix;
    for (int i = 0; i < kLedLength; i++) {
      ix = (m_currentPixel + i) % ncolors;
      m_ledBuffer[i].SetTrue_H360_S_V(colors[ix][0], colors[ix][1], colors[ix][2]);
    }
    m_ledA.SetData(m_ledBuffer);
    // m_ledB.SetData(m_ledBuffer);
    m_currentPixel = (m_currentPixel + 1) % kLedLength;
  }
}

void LEDs::Kitt() {
  if (--m_delay <= 0) {
    m_delay = 1;

    for (int i = 0; i < kLedLength; i++) {
      int r = m_ledBuffer[i].GetR;
      int g = m_ledBuffer[i].GetG;
      int b = m_ledBuffer[i].GetB;
      if (r >= 10) r -= 10; else r = 0;
      if (g >= 20) g -= 20; else g = 0;
      if (b >= 20) b -= 20; else b = 0;
      m_ledBuffer[i].SetTrue_R_G_B(r, g, b);
    }
    m_ledBuffer[m_currentPixel].SetTrue_R_G_B(64, 64, 64);
    m_ledA.SetData(m_ledBuffer);
    // m_ledB.SetData(m_ledBuffer);

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
    //printf("voltage: %f meter: %d\n", voltage, meter);

    for (int i = 0; i < kLedLength; i++) {
      if (i <= meter) {
        m_ledBuffer[i].SetTrue_R_G_B(0, 128, 0);
      } else {
        m_ledBuffer[i].TurnOff;
      }
    }
    m_ledA.SetData(m_ledBuffer);
    // m_ledB.SetData(m_ledBuffer);
  }
}

void LEDs::Disabled() {
  if (--m_delay <= 0) {
    m_delay = 30;

    for (int i = 0; i < kLedLength; i++) {
        m_ledBuffer[i].SetTrue_R_G_B(255, 48, 0);
    }
    m_ledA.SetData(m_ledBuffer);
    // m_ledB.SetData(m_ledBuffer);
  }
}

void LEDs::Teleop() {
  if (--m_delay <= 0) {
    m_delay = 30;

    for (int i = 0; i < kLedLength; i++) {
      if (m_alliance == frc::DriverStation::Alliance::kRed) {
        m_ledBuffer[i].SetTrue_R_G_B(192, 0, 0);
      } 
      else if (m_alliance == frc::DriverStation::Alliance::kBlue) {
        m_ledBuffer[i].SetTrue_R_G_B(0, 0, 192);
      } 
      else {
        m_ledBuffer[i].SetTrue_R_G_B(0, 192, 0);
      }
    }
    m_ledA.SetData(m_ledBuffer);
    // m_ledB.SetData(m_ledBuffer);
  }
}
void LEDs::ClimbTime() {
  if (--m_delay <= 0) {
    m_delay = 10;

      for (int i = 0; i < kLedLength; i++) {
        if (m_blink) {
          m_ledBuffer[i].TurnOff;
        } else {
          m_ledBuffer[i].SetTrue_R_G_B(0, 192, 0);
        }
      }
    m_ledA.SetData(m_ledBuffer);
    // m_ledB.SetData(m_ledBuffer);
    m_blink = 1 - m_blink;
  }
}
#endif // ENABLE_LED
