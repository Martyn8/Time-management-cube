#include "rtc.h"

RTC_DS3231 rtc;

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
  startOfActTime = startTime.timestamp(DateTime::TIMESTAMP_TIME);

  Serial.println("\nSTART COUNTING");
  Serial.println("startOfActDate: " + startOfActDate);
  Serial.println("startOfActTime: " + startOfActTime);
  Serial.println("\n");
}

/*
  Function responsible for calculating time when cube was lying on one of its sides;
*/
void calculateTime(void)
{
  endTime = rtc.now();
  endOfActTime = endTime.timestamp(DateTime::TIMESTAMP_TIME);
  endOfActDate = endTime.timestamp(DateTime::TIMESTAMP_DATE);

  String srt_date_time = startOfActDate + "T" + startOfActTime;
  char buffer[srt_date_time.length() + 1];
  srt_date_time.toCharArray(buffer, srt_date_time.length() + 1, 0);
  DateTime startTime = DateTime(buffer);
  String datetime_str = startTime.timestamp(DateTime::TIMESTAMP_FULL);

  activityDuration = DateTime(SECONDS_FROM_1970_TO_2000 + (endTime.secondstime() - startTime.secondstime()));

  char buff[] = "hh:mm:ss";
  String dur = activityDuration.toString(buff);

  Serial.println("\nCALCULATE TIME");
  Serial.println("endOfActTime: " + endOfActTime);
  Serial.println("startOfActTime: " + startOfActTime);
  Serial.println("srt_date_time: " + srt_date_time);
  Serial.println("datetime_str: " + datetime_str);
  Serial.println("dur: " + dur);
  Serial.println("\n");
}