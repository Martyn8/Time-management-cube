#ifndef accel_h
#define accel_h

#include <Adafruit_LSM6DS33.h>

extern Adafruit_LSM6DS33 lsm6ds33; // accelerometer, gyroscope

/*
 * Variable holding the wll on which the device lays
 */
extern String activeWall;

extern float accel_x, accel_y, accel_z;


/**************************************************ACCELEROMETER*****************************************************/
/*
  Function responsible for accelerometer and gyroscope readings;
  Prints readings every second on serial port
*/
void accelRead(void);

#endif