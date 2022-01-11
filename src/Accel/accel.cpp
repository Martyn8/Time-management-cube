#include "accel.h"

Adafruit_LSM6DS33 lsm6ds33; // accelerometer, gyroscope

/*
 * Variable holding the wll on which the device lays
 */
String activeWall = "";

float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;

unsigned long lastTime = 0;
const unsigned long accelReadDelay = 1000;

/**************************************************ACCELEROMETER*****************************************************/
/*
  Function responsible for accelerometer and gyroscope readings;
  Prints readings every second on serial port
*/
void accelRead(void)
{
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);
  accel_x = accel.acceleration.x;
  accel_y = accel.acceleration.y;
  accel_z = accel.acceleration.z;
  gyro_x = gyro.gyro.x;
  gyro_y = gyro.gyro.y;
  gyro_z = gyro.gyro.z;

  // Serial.print("Acceleration: ");
  // Serial.print(accel_x);
  // Serial.print(" ");
  // Serial.print(accel_y);
  // Serial.print(" ");
  // Serial.print(accel_z);
  // Serial.println(" m/s^2");

  // if ((millis() - lastTime) > accelReadDelay)
  // {
  //   sensors_event_t accel;
  //   sensors_event_t gyro;
  //   sensors_event_t temp;
  //   lsm6ds33.getEvent(&accel, &gyro, &temp);
  //   accel_x = accel.acceleration.x;
  //   accel_y = accel.acceleration.y;
  //   accel_z = accel.acceleration.z;
  //   gyro_x = gyro.gyro.x;
  //   gyro_y = gyro.gyro.y;
  //   gyro_z = gyro.gyro.z;

  //   Serial.println("\naccelRead");
  //   Serial.println("---------------------------------------------");

  //   Serial.print("Acceleration: ");
  //   Serial.print(accel_x);
  //   Serial.print(" ");
  //   Serial.print(accel_y);
  //   Serial.print(" ");
  //   Serial.print(accel_z);
  //   Serial.println(" m/s^2");
  //   Serial.print("Gyro: ");
  //   Serial.print(gyro_x);
  //   Serial.print(" ");
  //   Serial.print(gyro_y);
  //   Serial.print(" ");
  //   Serial.print(gyro_z);
  //   Serial.println(" dps");

  //   lastTime = millis();
  // }
}