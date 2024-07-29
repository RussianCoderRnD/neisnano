#ifndef CALCULATION_H
#define CALCULATION_H

#include <Arduino.h>
#include <variables.h>
float calculation()
{
  uint8_t mVperAmp = 66;
  int RawValue = 0;
  uint16_t ACSoffset = 2462;
  float mit2 = 0.00;
  long sum = 0;
  const int samples = 10;
  for (int i = 0; i < samples; i++)
  {
    sum += analogRead(Pin_BATT);
    delay(10);
  }
  float averageValue = sum / samples;
  return averageValue * (2462 / (resolution - 1));
}

#endif