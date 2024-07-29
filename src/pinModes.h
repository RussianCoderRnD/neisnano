#ifndef PINMODES_H
#define PINMODES_H

#include <Arduino.h>   // Основная библиотека для Arduino
#include <variables.h> // Файл с объявлением переменных (здесь объявляются глобальные переменные)

//------------------- pinModes() START ---------------
void pinModes()
{
  for (size_t i = 0; i < 8; i++)
  {
    pinMode(ArrayLinePin[i], OUTPUT);
    digitalWrite(ArrayLinePin[i], LOW);
  }
  pinMode(Pin24v, OUTPUT);
  pinMode(Pin_MIT, INPUT);
  pinMode(Pin_BATT, INPUT);
  digitalWrite(Pin24v, HIGH);
  digitalWrite(PinSloth, LOW);
}
//--------------------- pinModes() END ---------------

#endif