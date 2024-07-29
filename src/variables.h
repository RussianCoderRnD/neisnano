#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>
#include <define.h>

float KZ = 8.0; 
boolean lG, pG, lP, pP, sTOP, zX, fOG = false;

uint8_t count = 0;
uint8_t count1 = 0;
uint8_t lol;
float mit = 0.0;
uint8_t temp;
String ArrayNamesLine[] = {"0","LEFT_GABARIT", "RIGHT_GABARIT", "LEFT_POVOROT", "RIGHT_POVOROT", "STOP_SIGNAL", "ZADNY_XOD", "TUMANKA"};
#define INIT_ADDR 1023                
#define INIT_KEY 50                   
float ArrayLineMit[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
int ArrayLinePin[] = {0,PinRelay_LEFT_GABARIT, PinRelay_RIGHT_GABARIT, PinRelay_LEFT_POVOROT, PinRelay_RIGHT_POVOROT, PinRelay_STOP_SIGNAL, PinRelay_ZADNY_XOD, PinRelay_TUMANKA}; // 24, 22, 23, 27, 25, 26, 28
uint32_t eepromTimer = 0;
boolean eepromFlag = false;
const int resolution = 1024;

#endif