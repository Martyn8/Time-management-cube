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
    Serial.println("\nFRAM WRITE NUM OF REC");

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = numberOfRecords.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrNum, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr = addrNum + 1;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrNum + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, numberOfRecords[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote number of records to fram, and addr :" + String(writeToAddr));
    showFram();
}

/*
 * Function responsible for writing in the number of a wall to the FRAM memory. 
 */
void framWriteActiveWall(String wallNumber)
{
    Serial.println("\nFRAM WRITE ACTIVE WALL");

    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = wallNumber.length();

    // Save the length (number of characters in string) to memory so the program
    // knows how many characters to read back.
    fram.writeEnable(true);
    fram.write8(addrActiveWall, stringLength);
    fram.writeEnable(false);

    //  // Keep track of what address to write to
    int writeToAddr = addrActiveWall + 1;
    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrActiveWall + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, wallNumber[i]);
        fram.writeEnable(false);
    }
    delay(100);
    Serial.println("wrote number of an active wall to fram, to addr: " + String(writeToAddr));
    showFram();
}

/*
 * Function responsible for writing in the number of a wall to the FRAM memory. 
 */
void framWriteWall(String wallNumber)
{
    Serial.println("\nFRAM WRITE WALL");

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
    Serial.println("wrote number of a wall to fram, to addr " + String(addrWall));
    showFram();
}

/*
 * Function responsible for writing in the start date of an activity to the FRAM memory. 
 */
void framWriteDate(String startOfActDate)
{
    Serial.println("\nFRAM WRITE DATE");

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
    Serial.println("date to fram - num of records: " + numberOfRecords);
    delay(100);

    //
    for (uint8_t i = 0; i < stringLength; i++)
    {
        writeToAddr = addrDate + i + 1;
        fram.writeEnable(true);
        fram.write8(writeToAddr, startOfActDate[i]);
        fram.writeEnable(false);
    }
    Serial.println("wrote date to fram to addr" + String(addrDate));
    showFram();
}

/*
 * Function responsible for writing in the start time of an activity to the FRAM memory. 
 */
void framWriteActStart(String startOfActTime)
{
    Serial.println("\nFRAM WRITE ACT START");
    // Count number of characters in myStr
    // The count does not include the null-terminator character '\0'
    uint8_t stringLength = startOfActTime.length();
    Serial.println("act start in write act start: " + startOfActTime);

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
    Serial.println("wrote act start to fram, to addr" + String(addrStart));
    showFram();
}

/*
 * Function responsible for writing in the duration of an activity to the FRAM memory. 
 */
void framWriteDuration(DateTime activityDuration)
{

    char buff[] = "hh:mm:ss";
    Serial.print("\nFRAM WRITE DURATION - act dur: ");
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
    Serial.println("wrote duration to fram, to addr " + String(addrDur));
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
    Serial.println("\nREAD NUMBER");
    uint8_t charlen = fram.read8(addrNum);

    char chardata;
    String dataout = String("");

    int lastaddr = addrNum + charlen;

    for (int a = addrNum + 1; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read number of records from fram, last addr " + String(lastaddr));
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the active wall from the FRAM memory.
 */
String framReadActiveWall()
{
    Serial.println("\nREAD ACTIVE WALL");
    uint8_t charlen = fram.read8(addrActiveWall);

    char chardata;
    String dataout = String("");

    int lastaddr = addrActiveWall + charlen;

    for (int a = addrActiveWall + 1; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read number of a wall from fram, last addr " + String(lastaddr));
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the wall from the FRAM memory.
 */
String framReadWall(uint8_t record)
{
    Serial.println("\nREAD WALL");
    uint8_t charlen = fram.read8(addrWall + 31 * record);

    char chardata;
    String dataout = String("");

    int lastaddr = addrWall + charlen + 31 * record;

    for (int a = addrWall + 1 + 31 * record; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read number of a wall from fram, last addr " + String(lastaddr));
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the activity start date from the FRAM memory.
 */
String framReadDate(uint8_t record)
{
    Serial.println("\nREAD DATE");
    uint8_t charlen = fram.read8(addrDate + 31 * int(record));

    char chardata;
    String dataout = String("");

    int lastaddr = addrDate + charlen + 31 * record;

    for (int a = addrDate + 1 + 31 * record; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read date from fram, last addr " + String(lastaddr));
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the activity start time from the FRAM memory.
 */
String framReadActStart(uint8_t record)
{
    Serial.println("\nREAD ACT START");
    uint8_t charlen = fram.read8(addrStart + 31 * int(record));
    int fak = int(addrStart) + 31 * int(record);
    Serial.println("fak " + String(fak));
    Serial.println("Num of records string " + String(record));
    Serial.println("charlen string " + String(charlen));

    //Serial.println("Num of records int" + int(numberOfRecords));
    //Serial.println("Num of records string int " + String(int(numberOfRecords)));

    char chardata;
    String dataout = String("");

    int lastaddr = addrStart + charlen + 31 * record;
    Serial.println("lastaddr " + String(lastaddr));
    delay(100);
    Serial.println("addrStart" + String(addrStart + 31 * record));
    delay(100);
    // Serial.println("meh");
    // delay(1000);

    for (int a = addrStart + 1 + 31 * record; a <= lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read act start from fram, last addr " + String(lastaddr));
    Serial.println("dataout " + dataout);
    return dataout;
}

/*
 * Function responsible for reading the duration of an activity from the FRAM memory. 
 */
String framReadDuration(uint8_t record)
{
    Serial.println("\nREAD DURATION");
    uint8_t charlen = fram.read8(addrDur + 31 * int(record));
    Serial.println("addrdur: " + addrDur);

    char chardata;
    String dataout = String("");

    int lastaddr = addrDur + charlen + 31 * record;

    for (int a = addrDur + 1 + 31 * record; a < lastaddr; a += 1)
    {
        chardata = fram.read8(a);
        dataout.concat(chardata);
    }
    Serial.println("read duration from fram, last addr " + String(lastaddr));
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