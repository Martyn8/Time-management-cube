#ifndef fram_h
#define fram_h

#include <SPI.h>
#include <Adafruit_FRAM_SPI.h>
//#include <string>
#include <Arduino.h>

#include "RTClib.h"

// /******FRAM******/
extern uint8_t FRAM_CS;

// //Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI

extern uint8_t FRAM_SCK;
extern uint8_t FRAM_MISO;
extern uint8_t FRAM_MOS;

extern Adafruit_FRAM_SPI fram;

extern uint16_t addrNum;
extern uint16_t addrNum;
extern uint16_t addrNum;
extern uint16_t addrNum;

void framWriteNumber();

void framWriteWall();

void framWriteDate(String startOfActDate);

void framWriteActStart(String startOfActTime);

void framWriteDuration(DateTime activityDuration);

String framReadNumber();

String framReadWall();

String framReadDate();

String framReadActStart();

String framReadDuration();

void showFram();

void writeDataToFram(String startOfActDate, String startOfActTime, DateTime activityDuration);

#endif