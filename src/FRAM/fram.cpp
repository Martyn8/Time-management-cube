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
uint16_t addrActiveWall = 0x03;
uint16_t addrWall = 0x05;
uint16_t addrDate = 0x07;
uint16_t addrStart = 0x12;
uint16_t addrDur = 0x1b;

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
    Serial.println("wrote number of records to fram, and addr :" + writeToAddr);
    showFram();
}

/*
 * Function responsible for writing in the number of a wall to the FRAM memory. 
 */
void framWriteActiveWall(String wallNumber)
{

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = wallNumber.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrActiveWall, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrActiveWall + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, wallNumber[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote number of an active wall to fram, ans addr: " + writeToAddr);
    showFram();
}

/*
 * Function responsible for writing in the number of a wall to the FRAM memory. 
 */
void framWriteWall(String wallNumber)
{

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = wallNumber.length();

    addrWall += 31 * numberOfRecords;

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
        writeToAddr = addrWall + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, wallNumber[i]);
        fram.writeEnable(false);
    }

    delay(100);
    Serial.println("wrote number of a wall to fram");
    showFram();
}

/*
 * Function responsible for writing in the start date of an activity to the FRAM memory. 
 */
void framWriteDate(String startOfActDate)
{

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = startOfActDate.length();

    addrDate += 31 * numberOfRecords;

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrDate, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr;
    Serial.println("date to fram num of records: " + numberOfRecords);
    delay(100);

    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrDate + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, startOfActDate[i]);
        fram.writeEnable(false);
        delay(50);
    }
    Serial.println("wrote date to fram");
    showFram();
}

/*
 * Function responsible for writing in the start time of an activity to the FRAM memory. 
 */
void framWriteActStart(String startOfActTime)
{
    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = startOfActTime.length();

    addrStart += 31 * numberOfRecords;

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
        writeToAddr = addrStart + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, startOfActTime[i]);
        fram.writeEnable(false);
        delay(50);
    }
    Serial.println("wrote act start to fram");
    showFram();
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

    addrDur += 31 * numberOfRecords;

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
        writeToAddr = addrDur + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, buff[i]);
        fram.writeEnable(false);
        delay(50);
    }
    Serial.println("wrote duration to fram");
    showFram();
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
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the active wall from the FRAM memory.
 */
String framReadActiveWall()
{
    uint8_t charlen = fram.read8(addrActiveWall);

    char chardata;
    String dataout = String("");

    int lastaddr = addrActiveWall + charlen;

    for (int a = addrActiveWall + 1; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read number of a wall from fram");
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the wall from the FRAM memory.
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
    Serial.println("dataout " + dataout);
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
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the activity start time from the FRAM memory.
 */
String framReadActStart()
{
    Serial.println("READ ACT START");
    uint8_t charlen = fram.read8(uint16_t(addrStart + 31 * int(numberOfRecords)));
    int fak = int(addrStart) + 31 * int(numberOfRecords);
    Serial.println("fak " + String(fak));
    Serial.println("Num of records string " + String(numberOfRecords));
    Serial.println("charlen string " + String(charlen));

    //Serial.println("Num of records int" + int(numberOfRecords));
    //Serial.println("Num of records string int " + String(int(numberOfRecords)));

    char chardata;
    String dataout = String("");

    int lastaddr = addrStart + charlen + 31 * numberOfRecords;
    Serial.println("lastaddr " + String(lastaddr));
    delay(1000);
    Serial.println("addrStart" + String(addrStart));
    delay(1000);
    // Serial.println("meh");
    // delay(1000);

    for (int a = addrStart + 1 + 31 * numberOfRecords; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
        Serial.println("a " + a);
        Serial.println("chardata: " + chardata);
        delay(1000);
    }
    Serial.println("read act start from fram");
    Serial.println("dataout " + dataout);
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
    Serial.println("dataout " + dataout);
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

void resetFram()
{

    for (uint16_t a = 0; a < 8192; a++)
    {
        int writeToAddr = addrNum + a;
        fram.writeEnable(true);
        fram.write8(writeToAddr, 0);
        fram.writeEnable(false);
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