#include "fram.h"
uint8_t numberOfRecords = 0;
// /******FRAM******/
uint8_t FRAM_CS = 6;

// //Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_CS);  // use hardware SPI

uint8_t FRAM_SCK = SCK;
uint8_t FRAM_MISO = 24;
uint8_t FRAM_MOSI = 25;

Adafruit_FRAM_SPI fram = Adafruit_FRAM_SPI(FRAM_SCK, FRAM_MISO, FRAM_MOSI, FRAM_CS);

uint16_t addrNum = 0x00;
uint16_t addrWall = 0x03;
uint16_t addrDate = 0x05;
uint16_t addrStart = 0x16;
uint16_t addrDur = 0x25;

/************************************************WRITE******TO*******FRAM*******************************************************/

/*
 * Function responsible for writing in the number of fecords to the FRAM memory. 
 */
void framWriteNumber(String numberOfRecords)
{
    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = numberOfRecords.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrNum, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrNum + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, numberOfRecords[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote number of records to fram");
}

/*
 * Function responsible for writing in the number of a wall to the FRAM memory. 
 */
void framWriteWall(String wallNumber)
{

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = wallNumber.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrWall, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrWall + i + 1 + 31 * numberOfRecords;
        fram.writeEnable(true);
        fram.write8(writeToAddr, wallNumber[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote number of a wall to fram");
}

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
    fram.write8(addrDate, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrDate + i + 1 + 31 * numberOfRecords;
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
    fram.write8(addrStart, stringLength);
    fram.writeEnable(false);
    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrStart + i + 1 + 31 * numberOfRecords;
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
    Serial.print("fram read dur - act dur: ");
    Serial.println(activityDuration.toString(buff));

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = 9;

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrDur, stringLength);
    fram.writeEnable(false);
    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrDur + i + 1 + 31 * numberOfRecords;
        fram.writeEnable(true);
        fram.write8(writeToAddr, buff[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote duration to fram");
}

/*
*
*/
/*********************************************READ*****FROM******FRAM********************************************************/
/*
 * Function responsible for reading the number of records from the FRAM memory.
 */
String framReadNumber()
{
    uint8_t charlen = fram.read8(addrNum);

    char chardata;
    String dataout = String("");

    int lastaddr = addrNum + charlen;

    for (int a = addrNum + 1; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read number of records from fram");
    return dataout;
}

/*
 * Function responsible for reading the activity start date from the FRAM memory.
 */
String framReadWall()
{
    uint8_t charlen = fram.read8(addrWall);

    char chardata;
    String dataout = String("");

    int lastaddr = addrWall + charlen;

    for (int a = addrWall + 1; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read number of a wall from fram");
    return dataout;
}

/*
 * Function responsible for reading the activity start date from the FRAM memory.
 */
String framReadDate()
{
    uint8_t charlen = fram.read8(addrDate);

    char chardata;
    String dataout = String("");

    int lastaddr = addrDate + charlen;

    for (int a = addrDate + 1; a <= lastaddr; a += 1)
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
    uint8_t charlen = fram.read8(addrStart);

    char chardata;
    String dataout = String("");

    int lastaddr = addrStart + charlen;

    for (int a = addrStart + 1; a <= lastaddr; a += 1)
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
    uint8_t charlen = fram.read8(addrDur);
    ;

    char chardata;
    String dataout = String("");

    int lastaddr = addrDur + charlen;

    for (int a = addrDur + 1; a <= lastaddr; a += 1)
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
    //for (uint16_t a = 0; a < 8192; a++)
    for (uint16_t a = 0; a < 200; a++)
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

void writeDataToFram(String activeWall, String startOfActDate, String startOfActTime, DateTime activityDuration)
{
    framWriteWall(activeWall);
    framWriteDate(startOfActDate);
    framWriteActStart(startOfActTime);
    framWriteDuration(activityDuration);
}