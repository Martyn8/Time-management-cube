#include "fram.h"

// /******FRAM******/
uint8_t FRAM_CS = 6;

// //Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI

uint8_t FRAM_SCK = SCK;
uint8_t FRAM_MISO = 24;
uint8_t FRAM_MOSI = 25;

Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_SCK, FRAM_MISO, FRAM_MOSI, FRAM_CS);

uint16_t addr = 0x0;

/************************************************WRITE******TO*******FRAM*******************************************************/
/*
 * Function responsible for writing in the start date of an activity to the FRAM memory. 
 */
void framWriteDate(String startOfActDate)
{

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = startOfActDate.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addr, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addr + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, startOfActDate[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote date to fram");
}

/*
 * Function responsible for writing in the start time of an activity to the FRAM memory. 
 */
void framWriteActStart(String startOfActTime)
{
    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = startOfActTime.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(0x12, stringLength);
    fram.writeEnable(false);
    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addr + i + 12;
        fram.writeEnable(true);
        fram.write8(writeToAddr, startOfActTime[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote act start to fram");
}

/*
 * Function responsible for writing in the duration of an activity to the FRAM memory. 
 */
void framWriteDuration(DateTime activityDuration)
{

    char buff[] = "hh:mm:ss";
    Serial.println(activityDuration.toString(buff));

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = 9;

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(0x21, stringLength);
    fram.writeEnable(false);
    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addr + i + 22;
        fram.writeEnable(true);
        fram.write8(writeToAddr, buff[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote duration to fram");
}

/*********************************************READ*****FROM******FRAM**********************8**********************************/
/*
 * Function responsible for reading the activity start date from the FRAM memory.
 */
String framReadDate()
{
    uint8_t charlen = fram.read8(addr);

    char chardata;
    String dataout = String("");

    int lastaddr = addr + charlen;

    for (int a = addr + 1; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read date from fram");
    return dataout;
}

/*
 * Function responsible for reading the activity start time from the FRAM memory.
 */
String framReadActStart()
{
    uint8_t charlen = 8;

    char chardata;
    String dataout = String("");

    int lastaddr = 12 + charlen;

    for (int a = 12; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read act start from fram");
    return dataout;
}

/*
 * Function responsible for reading the duration of an activity from the FRAM memory. 
 */
String framReadDuration()
{
    uint8_t charlen = 8;

    char chardata;
    String dataout = String("");

    int lastaddr = 22 + charlen;

    for (int a = 22; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read duration from fram");
    return dataout;
}

/*********************************************************************/
/*
 * Function responsible for printing out the entire FRAM memory. 
 */
void showFram()
{
    uint8_t value;
    for (uint16_t a = 0; a < 8192; a++)
    {
        value = fram.read8(a);
        if ((a % 32) == 0)
        {
            Serial.print("\n 0x");
            Serial.print(a, HEX);
            Serial.print(": ");
        }
        Serial.print("0x");
        if (value < 0x1)
            Serial.print('0');
        Serial.print(value, HEX);
        Serial.print(" ");
    }
}

/************************************************************************/

void writeDataToFram(String startOfActDate, String startOfActTime, DateTime activityDuration)
{
    framWriteDate(startOfActDate);
    framWriteActStart(startOfActTime);
    framWriteDuration(activityDuration);
}