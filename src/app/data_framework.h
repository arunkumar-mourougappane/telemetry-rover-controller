#ifndef DATA_FRAMWORK_H
#define DATA_FRAMWORK_H
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <atomic>

typedef enum
{
   NONE = 0,
   UP = 1,
   UPPER_RIGHT = 2,
   RIGHT = 3,
   DOWN_RIGHT = 4,
   DOWN = 5,
   DOWN_LEFT = 6,
   LEFT = 7,
   UPPER_LEFT = 8,
} Direction_e;

typedef struct
{
   std::atomic<bool> dataReady;
   uint16_t xAxisAnalog;
   uint16_t yAxisAnalog;
   std::atomic<bool> buttonPress;
   Direction_e direction;
} direction_t;


typedef struct
{
   std::atomic<bool> ready;
   float GyroX;
   float GyroY;
   float GyroZ;
   float AccX;
   float AccY;
   float AccZ;
   float MagX;
   float MagY;
   float MagZ;
   float temperature;
} Mpu9250_t;

#endif // !DATA_FRAMWORK_H