/* ULN2003 stepper motor */

#include "uln.hpp"
#include <Arduino.h>

const uint8_t ro1 = D8;
const uint8_t ro2 = D7;
const uint8_t ro3 = D6;
const uint8_t ro4 = D0;
const uint8_t lo1 = D1;
const uint8_t lo2 = D2;
const uint8_t lo3 = D3;
const uint8_t lo4 = D4;


void init_drive()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D0, OUTPUT);
}

void setULN(int t, uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4)
{
  uint8_t array[4];
  for (int i = 0; i < 4; i++)
    array[i] = LOW;
  if (t % 2)
  {
    t /= 2;
    array[t % 4] = HIGH;
    array[(t + 1) % 4] = HIGH;
  }
  else
  {
    t /= 2;
    array[t % 4] = HIGH;
  }
  digitalWrite(o1, array[0]);
  digitalWrite(o2, array[1]);
  digitalWrite(o3, array[2]);
  digitalWrite(o4, array[3]);
}

int tr = 0;
int tl = 0;

void driveRight(int t)
{
  setULN(t, ro1, ro2, ro3, ro4);
}

void driveLeft(int t)
{
  setULN(t, lo1, lo2, lo3, lo4);
}
