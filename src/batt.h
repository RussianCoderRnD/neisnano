#ifndef BATT_H
#define BATT_H
#include <Arduino.h>
#include <variables.h>
float Batt()
{
  long sum = 0;
  const int samples = 10;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(Pin_BATT);
    delay(10);
  }
  float averageValue = sum / samples;
  float voltage = (analogRead(A0) * 5.0) / 1024;
float val = (100/5.0)*(voltage*1.9);
return val;
}

#endif