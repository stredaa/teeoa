#include "hardware/MPU6050.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <cmath>
#include <stdint.h>

#define MPU6050_ACCELERATOR_CONFIG 0x1c
#define MPU6050_GYROSCOPE_CONFIG 0x1b
#define MPU6050_POWER_MGMT 0x6b
#define MPU6050_ACCEL_OUT 0x3b

#define MPU6050_ADDRESS 0x68
#define MPU6050_ACCEL_SCALE 16384.0
#define MPU6050_GYRO_SCALE 131.0
#define MPU6050_TEMPERATURE_SCALE 340.0

struct MPUData{
    double acc_x;
    double acc_y;
    double acc_z;
    double temperature;
    double gyro_x;
    double gyro_y;
    double gyro_z;
};

MPUData internalState = MPUData();

void initializeMPU() {
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_POWER_MGMT);
    Wire.write(0);
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_ACCELERATOR_CONFIG);
    Wire.write(0);
    Wire.endTransmission(true);

    Wire.endTransmission(true);
    Wire.write(MPU6050_GYROSCOPE_CONFIG);
    Wire.write(0);
    Wire.endTransmission(true);
}

void updateMPUData(MPUData *result)
{
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(MPU6050_ACCEL_OUT);
    Wire.requestFrom((uint8_t)MPU6050_ADDRESS, (size_t)14, true);

    int16_t buffer[7];
    for (int i = 0; i < 7; i++)
    {
        buffer[i] = Wire.read() << 8 | Wire.read();
    }

    result->acc_x = buffer[0] / MPU6050_ACCEL_SCALE;
    result->acc_y = buffer[1] / MPU6050_ACCEL_SCALE;
    result->acc_z = buffer[2] / MPU6050_ACCEL_SCALE;
    result->temperature = (buffer[3] / MPU6050_TEMPERATURE_SCALE) + 36.53;
    result->gyro_x = buffer[4] / MPU6050_GYRO_SCALE;
    result->gyro_y = buffer[5] / MPU6050_GYRO_SCALE;
    result->gyro_z = buffer[6] / MPU6050_GYRO_SCALE;

    Wire.endTransmission();
}
