#ifndef fram_h
#define fram_h

#include <SPI.h>
#include <Adafruit_FRAM_SPI.h>
//#include <string>
#include <Arduino.h>

#include "RTClib.h"

extern uint8_t numberOfRecords;

// /******FRAM******/
extern uint8_t FRAM_CS;

// //Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI

extern uint8_t FRAM_SCK;
extern uint8_t FRAM_MISO;
extern uint8_t FRAM_MOS;

extern Adafruit_FRAM_SPI fram;

extern uint16_t addrNum;
extern uint16_t addrActiveWall;
extern uint16_t addrWall;
extern uint16_t addrDate;
extern uint16_t addrStart;
extern uint16_t addrDur;

void framWriteNumber(String numberOfRecords);

void framWriteActiveWall(String wallNumber);

void framWriteWall(String wallNumber);

void framWriteDate(String startOfActDate);

void framWriteActStart(String startOfActTime);

void framWriteDuration(DateTime activityDuration);

String framReadNumber();

String framReadActiveWall();

String framReadWall(uint8_t record);

String framReadDate(uint8_t record);

String framReadActStart(uint8_t record);

String framReadDuration(uint8_t record);

void showFram();

void resetFram();

void writeDataToFram(String activeWall, String startOfActDate, String startOfActTime, DateTime activityDuration);

#endif