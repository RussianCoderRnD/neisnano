#include <Arduino.h>
#include <variables.h>
#include <libraries.h>
uint32_t tmr;
String str;
#define RX_PIN A3
#define TX_PIN A4
SoftwareSerial SerialPort(RX_PIN, TX_PIN);
typedef struct struct_Data
{
  float LG;
  float PG;
  float LP;
  float PP;
  float STOP;
  float ZX;
  float FOG;
  float BATT;
} struct_Data;

struct_Data myData;

typedef struct struct_In
{
  uint8_t count = 0;
  uint8_t res1 = 0;

} struct_In;

struct_In inData;

void sendStructure(byte *structurePointer, int structureLength)
{
  SerialPort.write(structurePointer, structureLength);
}

void recieveStructure(byte *structurePointer, int structureLength)
{
  if (SerialPort.available() < sizeof(inData))
    return;
  SerialPort.readBytes(structurePointer, structureLength);
}
void inNodeMCU();
void NameLinePin(uint8_t);
void testLine();
void setBright();
void _green();
void checkEEPROM();
void EEPROMRead();
void Menu();
void setup()
{
  delay(5000);
  lols++;
  setBright();
  lol(lols);
  Serial.begin(115200);
  SerialPort.begin(9600);

  EEPROMRead();
  pinModes();
}
void loop()
{
  recieveStructure((byte *)&inData, sizeof(inData));
  count = inData.count;
  Menu();
  tmr = millis();
  if (inData.res1 == 1)
  {
    count = 0;
    testLine();
    myData.LG = ArrayLineMit[1];
    myData.PG = ArrayLineMit[2];
    myData.LP = ArrayLineMit[3];
    myData.PP = ArrayLineMit[4];
    myData.STOP = ArrayLineMit[5];
    myData.ZX = ArrayLineMit[6];
    myData.FOG = ArrayLineMit[7];
    myData.BATT = Batt();
    sendStructure((byte *)&myData, sizeof(myData));
    count = inData.res1 = 0;
  }
  checkEEPROM();
}
void inNodeMCU()
{
  String str;
  str = String(String("LG ") + String(1) + String(" PG ") + String(2) + String(" LP ") + String(3) + String(" PP ") + String(4) + String(" STOP ") + String(5) + String(" ZX ") + String(6) + String(" FOG ") + String(7) + String(" BATT ") + String(8) + String(" count ") + String(count));
  Serial.println(str);
}

void NameLinePin(uint8_t Nam_LINE)
{
  uint8_t mVperAmp = 100;
  int RawValue = 0;
  uint16_t ACSoffset = 2500;
  digitalWrite(Nam_LINE, HIGH);
  delay(500);

  RawValue = analogRead(Pin_MIT);
  mit = ((((RawValue / 1023.0) * (ACSoffset * 2)) - ACSoffset) / mVperAmp);
  if (mit <= 0.70)
  {
    mit = 0.00;
  }
  mit = (mit - 0.6);
  delay(10);
  digitalWrite(Nam_LINE, LOW);
}
void testLine()
{
  for (int y = 0; y < 8;)
  {
    NameLinePin(ArrayLinePin[y]);
    ArrayLineMit[y] = mit;
    Serial.println();
    Serial.print(ArrayNamesLine[y]);
    Serial.print(" - ");
    Serial.print(ArrayLineMit[y]);
    Serial.println();
    y++;
  }
}
void setBright()
{
  lols = constrain(lols, 0, 100); // ограничили от 0 до 100
  eepromFlag = true;              // поднять флаг
  eepromTimer = millis();         // сбросить таймер
}
void checkEEPROM()
{

  if (eepromFlag && (millis() - eepromTimer >= 500))
  {                      // если флаг поднят и с последнего нажатия прошло 10 секунд (10 000 мс)
    eepromFlag = false;  // опустили флаг
    EEPROM.put(0, lols); // записали в EEPROM
  }
}

void EEPROMRead()
{
  if (EEPROM.read(INIT_ADDR) != INIT_KEY)
  {                                    // первый запуск (ЕСЛИ INIT_ADDR (1023)не равен INIT_KEY (50) то записать EEPROM.write(INIT_ADDR, INIT_KEY);EEPROM.put(0, izmenenieTemp);
    EEPROM.write(INIT_ADDR, INIT_KEY); // записали ключ
    EEPROM.put(0, lols);               // записали стандартное значение температуры. в данном случае это значение переменной, объявленное выше
  }
  EEPROM.get(0, lols); // прочитали температуру
}

void Menu()
{
  if (count > 7)
  {
    count = 0;
  }
  if (count < 0)
  {
    count = 7;
  }
  if (count == 1 && ArrayLineMit[0] != KZ)
  {
    digitalWrite(PinRelay_LEFT_GABARIT, HIGH);
    Serial.println(" -LEFT_GABARIT ");
  }
  else
  {
    digitalWrite(PinRelay_LEFT_GABARIT, LOW);
  }

  if (count == 2 && ArrayLineMit[1] != KZ)
  {
    digitalWrite(PinRelay_RIGHT_GABARIT, HIGH);
    Serial.println(" -RIGHT_GABARIT ");
  }
  else
  {
    digitalWrite(PinRelay_RIGHT_GABARIT, LOW);
  }

  if (count == 3 && ArrayLineMit[2] != KZ)
  {
    digitalWrite(PinRelay_LEFT_POVOROT, HIGH);
    Serial.println(" -LEFT_POVOROT ");
  }
  else
  {
    digitalWrite(PinRelay_LEFT_POVOROT, LOW);
  }

  if (count == 4 && ArrayLineMit[3] != KZ)
  {
    digitalWrite(PinRelay_RIGHT_POVOROT, HIGH);
    Serial.println(" - RIGHT_POVOROT ");
  }
  else
  {
    digitalWrite(PinRelay_RIGHT_POVOROT, LOW);
  }

  if (count == 5 && ArrayLineMit[4] != KZ)
  {
    digitalWrite(PinRelay_STOP_SIGNAL, HIGH);
    Serial.println(" - STOP_SIGNAL");
  }

  else
  {
    digitalWrite(PinRelay_STOP_SIGNAL, LOW);
  }

  if (count == 6 && ArrayLineMit[5] != KZ)
  {
    digitalWrite(PinRelay_ZADNY_XOD, HIGH);
    Serial.println(" - ZADNY_XOD");
  }
  else
  {
    digitalWrite(PinRelay_ZADNY_XOD, LOW);
  }

  if (count == 7 && ArrayLineMit[6] != KZ)
  {
    digitalWrite(PinRelay_TUMANKA, HIGH);
    Serial.println(" - TUMANKA");
  }
  else
  {
    digitalWrite(PinRelay_TUMANKA, LOW);
  }
}