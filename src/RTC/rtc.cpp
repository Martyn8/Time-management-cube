#include "rtc.h"

RTC_DS1307 rtc;

/*
 * Variables holding readings from the RTC 
 */
DateTime startTime;
DateTime endTime;

/*
 * Variables holding timestamps of the time and date of the start and end of an activity 
 */
String startOfActTime;
String endOfActTime;
String startOfActDate;
String endOfActDate;

/*
 * Variable holding the duration of an activity
 */
DateTime activityDuration;

/*********************************************TIME*************CALCULATING*************************************************/
/*
  Function responsible for setting the start time of an activity;
*/
void startCounting(void)
{
  startTime = rtc.now();

  startOfActDate = startTime.timestamp(DateTime::TIMESTAMP_DATE);
  Serial.println("start count - start date: " + startOfActDate);
  startOfActTime = startTime.timestamp(DateTime::TIMESTAMP_TIME);
  Serial.println("start count - start time: " + startOfActTime);
}

/*
  Function responsible for calculating time when cube was lying on one of its sides;
*/
void calculateTime(void)
{
  endTime = rtc.now();
  endOfActTime = endTime.timestamp(DateTime::TIMESTAMP_TIME);
  endOfActDate = endTime.timestamp(DateTime::TIMESTAMP_DATE);
  Serial.println("calculate time - end time: " + endOfActTime);
  Serial.println("calculate time - end date: " + endOfActDate);
  activityDuration = DateTime(SECONDS_FROM_1970_TO_2000 + (endTime.secondstime() - startTime.secondstime()));

  char buff[] = "hh:mm:ss";
  Serial.print("calculate time - act dur: ");
  Serial.println(activityDuration.toString(buff));
  String dur = activityDuration.toString(buff);
  Serial.println("calculate time -  dur: " + dur);
  delay(100);
}