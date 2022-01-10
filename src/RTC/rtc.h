#ifndef rtc_h
#define rtc_h

#include <Arduino.h>
#include "RTClib.h"



extern RTC_DS1307 rtc;

/*
 * Variables holding readings from the RTC 
 */
extern DateTime startTime;
extern DateTime endTime;

/*
 * Variables holding timestamps of the time and date of the start and end of an activity 
 */
extern String startOfActTime;
extern String endOfActTime;
extern String startOfActDate;
extern String endOfActDate;

/*
 * Variable holding the duration of an activity
 */
extern DateTime activityDuration;

/*********************************************TIME*************CALCULATING*************************************************/
/*
  Function responsible for setting the start time of an activity;
*/
void startCounting(void);

/*
  Function responsible for calculating time when cube was lying on one of its sides;
*/
void calculateTime(void);

#endif