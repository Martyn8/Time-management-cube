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
  //Serial.println("start count - start date: " + startOfActDate);
  startOfActTime = startTime.timestamp(DateTime::TIMESTAMP_TIME);
  //Serial.println("start count - start time: " + startOfActTime);
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
  //DateTime::time

  String srt_date_time = startOfActDate + "T" + startOfActTime;

  char buffer[srt_date_time.length() + 1];

  srt_date_time.toCharArray(buffer, srt_date_time.length(), 0);

  DateTime startTime = DateTime(buffer);

  Serial.println("calculate time - start act time: " + startOfActTime);

  Serial.println("calculate time - start date: " + startOfActDate);

  String datetime_str = startTime.timestamp(DateTime::TIMESTAMP_FULL);
  Serial.println("calculate time - start DateTime: " + datetime_str);

  activityDuration = DateTime(SECONDS_FROM_1970_TO_2000 + (endTime.secondstime() - startTime.secondstime()));

  Serial.print("calculate time - act dur: ");

  char buff[] = "hh:mm:ss";
  Serial.println(activityDuration.toString(buff));
  String dur = activityDuration.toString(buff);
  Serial.println("calculate time -  dur: " + dur);
  delay(100);
}