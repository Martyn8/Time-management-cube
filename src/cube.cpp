#include <Arduino.h>

#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

#include <Adafruit_Sensor.h>

#include <Adafruit_TinyUSB.h> // for Serial

#include "FRAM\fram.h"
#include "RTC\rtc.h"
#include "Bluetooth\ble.h"
#include "NeoPixel\neoPixel.h"
#include "Accel\accel.h"

/*
 * The variable holding the pin to which the interrupt is sent from the accelerometer 
 */
#define WAKE_HIGH_PIN 3

/*
 * Variable holding the time window before the device is being put in power off mode
 */
#define SLEEPING_DELAY 20000

/********************************************************Send data**************************************************************/

void sendDataToDevice()
{
  Serial.println("\nSEND DATA TO DEVICE");
  //uint8_t i = 0;

  String DATA = String(numberOfRecords);

  for (uint8_t i = 0; i < numberOfRecords; i++)
  {
    Serial.println("\n");
    String readWall = framReadWall(i);
    Serial.println("Wall: " + readWall + "\n");

    Serial.println("\n");
    String readDate = framReadDate(i);
    Serial.println("Date: " + readDate + "\n");

    String readTime = framReadActStart(i);
    Serial.println("Time: " + readTime + "\n");

    String readDur = framReadDuration(i);
    Serial.println("Duration: " + readDur + "\n");

    String timestamp = readDate + " " + readTime;

    DATA += readWall + readDate + readTime + readDur;

    Serial.println("DATA: " + DATA);
  }

  Serial.println("DATA: " + DATA);

  DATA += "END";

  char charBuf[DATA.length() + 1];

  DATA.toCharArray(charBuf, DATA.length() + 1, 0);

  if (IS_CONNECTED == 1)
  {
    Serial.println("IS_CONNECTED");

    bleuart.write(charBuf);

    Serial.println("charBuf: " + String(charBuf));

    Serial.println("data has been sent");

    resetFram();

    showFram();
  }
  else
    Serial.println("IS_NOT_CONNECTED");
}

/******************************************************SLEEP******************************************************************/
/*
  Function responsible for putting cube in system off mode;
*/
void sleep(unsigned long time)
{
  //Serial.println(" going to sleep in 5 s ");
  //Serial.println("function sleep - active wall: " + activeWall);
  if (activeWall == "S") //go into deep sleep
  {
    //Serial.println(" go deep zzz in 10s");
    while (accel_z > 9)
    {
      accelRead(); //check if position was changed
      // shutdown when time reaches SLEEPING_DELAY ms
      if (((millis() - time) > SLEEPING_DELAY))
      {
        Serial.println(" go deep zzz");
        //to reduce power consumption when sleeping, turn off all your LEDs (and other power hungry devices)
        digitalWrite(LED_BUILTIN, LOW);
        Bluefruit.autoConnLed(false);
        // setup wake-up pin
        pinMode(WAKE_HIGH_PIN, INPUT_PULLDOWN_SENSE);
        //showFram();
        //Serial.println("deep sleep");
        activeWall = "";
        framWriteActiveWall(activeWall);
        //Serial.println("wrote active wall to fram ");
        delay(1000);

        sd_power_system_off(); // power down nrf52
      }
    }
  }
  else
  { //go to sleep after starting counting
    //Serial.println(" go light zzz in 10s");
    while (!lsm6ds33.awake())
    {
      if (((millis() - time) > SLEEPING_DELAY))
      {
        //Serial.println(" go light zzz");
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);

        pinMode(WAKE_HIGH_PIN, INPUT_PULLDOWN_SENSE);
        delay(100);
        //Serial.println("light sleep");
        //delay(100);
        sd_power_system_off(); // power down nrf52
      }
    }
  }
}

/****************************************SETTING*******ACTIVE*******WALL****************************************************/
/*
 * Function responsible for determining the wall on which the device is currently located 
 */
void setActiveWall(void)
{
  if (accel_x > 9)
  {
    activeWall = "1";
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_x < -9)
  {
    activeWall = "3";
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_y > 9)
  {
    activeWall = "2";
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_y < -9)
  {
    activeWall = "4";
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_z > 9)
  {
    activeWall = "S";
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_z < -9)
  {
    activeWall = "5";
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else
  {
    activeWall = "undefined";
    Serial.println("\nThe cube lays in an " + activeWall + " position\n");
  }
  neoPixelShow(activeWall);
}

/*************************************************************************************************************************/

/*************************************************************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  // while (!Serial) delay(10);
  Serial.println("Feather Sense Cube Demo");

  NeoPixel.begin();
  NeoPixel.setBrightness(50);
  NeoPixel.show();

  Bluefruit.autoConnLed(false);

  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(4); // Check bluefruit.h for supported values
  Bluefruit.setName("Bluefruit52");
  //Bluefruit.setName(getMcuUniqueID()); // useful testing with multiple central connections
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // To be consistent OTA DFU should be added first if it exists
  bledfu.begin();

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather52");
  bledis.begin();

  // Configure and Start BLE Uart Service
  bleuart.begin();

  // Start BLE Battery Service
  blebas.begin();
  blebas.write(100);

  // Set up and start advertising
  startAdv();

  // initialize the sensors

  if (!lsm6ds33.begin_I2C())
  {
    // if (!lsm.begin_SPI(LSM_CS)) {
    // if (!lsm.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    Serial.println("Failed to find LSM6DS33 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("LSM6DS33 Found!");

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(500);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(500);
  // digitalWrite(LED_BUILTIN, LOW);

  //accelerometer setup
  // Set to 2G range and 26 Hz update rate
  lsm6ds33.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  lsm6ds33.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
  lsm6ds33.setAccelDataRate(LSM6DS_RATE_26_HZ);
  lsm6ds33.setGyroDataRate(LSM6DS_RATE_26_HZ);

  //lsm6ds33.configIntOutputs(false, true);

  // wakeup detect output on INT1
  lsm6ds33.configInt1(false, false, false, false, true);

  lsm6ds33.enableWakeup(true, 10, 10);

  //RTC setup
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  else
  {
    Serial.println("Found RTC");
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  //FRAM setup
  if (fram.begin())
  {
    Serial.println("Found SPI FRAM");
    fram.writeEnable(true);
    //uint8_t values[2] = {48, 48};
    //fram.write(1, values, sizeof(values) / sizeof(*values));
    //resetFram();
    //Serial.println("reset SPI FRAM");
    showFram();
    Serial.println("show SPI FRAM setup");
    fram.writeEnable(false);
  }
  else
  {
    Serial.println("No SPI FRAM found ... check your connections\r\n");
    while (1)
      ;
  }
}

/*************************************************************************************************************************/

/*************************************************************************************************************************/

void loop(void)
{

  if (lsm6ds33.awake())
  {
    delay(5000);
    Serial.println(" Motion detected ");

    digitalWrite(LED_BUILTIN, HIGH);

    delay(500);

    digitalWrite(LED_BUILTIN, LOW);
    delay(500);

    digitalWrite(LED_BUILTIN, HIGH);

    accelRead();

    activeWall = framReadActiveWall();
    Serial.println("activeWall after motion: " + activeWall);
    delay(100);

    String numOFREcords = framReadNumber();
    Serial.println("numOFREcords string in motion detect: " + numOFREcords);
    delay(100);
    numberOfRecords = numOFREcords.toInt();
    Serial.println("numberOfRecords string in motion detect: " + String(numberOfRecords));

    if (activeWall.length() == 0)
    {
      Serial.println("\n\nFIRST TIME WAKE UP\n");

      //if cube was in deep sleep (on "S" wall)
      //set activeWall for the first time and start counting or go to sleep if it is "S" wall

      setActiveWall();
      Serial.println("active wall after deep sleep: " + activeWall);

      if (activeWall == "S")
      {
        Serial.println("ACTIVE WALL SSSSSSS");
        Serial.println("number of records: " + String(numberOfRecords));
        if (numberOfRecords != 0)
        {
          sendDataToDevice();
        }

        sleep(millis());
      }
      else if (activeWall == "undefined")
      {
        //wait for motion detect
      }
      else // if wall num is 1-5
      {
        startCounting();
        //writeDataToFram(activeWall, startOfActDate, startOfActTime, activityDuration);
        Serial.println(" first time - startOfActDate " + startOfActDate);
        Serial.println(" first time - startOfActTime " + startOfActTime);
        framWriteActiveWall(activeWall);
        framWriteWall(activeWall);
        framWriteDate(startOfActDate);
        framWriteActStart(startOfActTime);

        Serial.println("\nFRAM AFTER START COUNT FOR FIRST TIME");
        showFram();
        Serial.println("\n");
        sleep(millis());
      }
    }
    else
    {
      //if cube was active but wall was changed

      //bicz mejbi rid that dejta?????????????

      startOfActDate = framReadDate(numberOfRecords);
      startOfActTime = framReadActStart(numberOfRecords);

      Serial.println("is startOfActDate correct after light sleep : " + startOfActDate);
      Serial.println("is startOfActTime correct after light sleep : " + startOfActTime);
      String previousWall = activeWall;
      Serial.println("previous active wall after position change: " + previousWall);
      setActiveWall();
      Serial.println("new active wall after position change: " + activeWall);

      if (activeWall != previousWall) //new activity
      {
        Serial.println("activeWall != previousWall");
        if (activeWall == "S") //new wall is "S" wall
        {
          Serial.println("ACTIVE WALL SSSSSSS");
          calculateTime();
          Serial.println(" new S wall - startOfActDate " + startOfActDate);
          Serial.println(" new S wall - startOfActTime " + startOfActTime);

          //writeDataToFram(activeWall, startOfActDate, startOfActTime, activityDuration);
          framWriteDuration(activityDuration);

          numberOfRecords += 1;
          Serial.println("num of rec after writing dur" + numberOfRecords);
          showFram();
          framWriteNumber(String(numberOfRecords));
          showFram();

          sendDataToDevice();

          sleep(millis());
        }
        else if (activeWall == "undefined")
        {
          //wait for motion detect
        }
        else //active wall is 1-5 wall
        {
          calculateTime();
          Serial.println(" new wall - startOfActDate " + startOfActDate);
          Serial.println(" new wall - startOfActTime " + startOfActTime);
          // String numOFREcords = framReadNumber();
          // Serial.println("records string: " + numOFREcords);
          // numberOfRecords = numOFREcords.toInt();
          // Serial.println("numberOfRecords: " + String(numberOfRecords));

          //writeDataToFram(activeWall, startOfActDate, startOfActTime, activityDuration);
          framWriteDuration(activityDuration);

          delay(2000);
          numberOfRecords++;
          Serial.println("num of rec string after writing dur " + String(numberOfRecords));
          delay(1000);
          showFram();
          framWriteNumber(String(numberOfRecords));
          Serial.println("NUM oF REC +1 TO FRAM\n");
          delay(1000);
          showFram();
          startCounting();
          Serial.println("STARTTED COUNTING\n");
          //writeDataToFram(activeWall, startOfActDate, startOfActTime, activityDuration);
          framWriteActiveWall(activeWall);
          framWriteWall(activeWall);
          framWriteDate(startOfActDate);
          framWriteActStart(startOfActTime);
          delay(1000);
          Serial.println("WROTE NEW ACT TO FRAM?????????????????????\n");
          delay(1000);
          showFram();
          delay(1000);
          sleep(millis());
        }
      }
      else
      { //(activeWall == previousWall) same activity
        sleep(millis());
      }
    }
  }
  delay(100); // can wait as long as you like!

  // Forward data from HW Serial to BLEUART
  while (Serial.available())
  {
    // Delay to wait for enough input, since we have a limited transmission buffer
    delay(2);

    uint8_t buf[64];
    int count = Serial.readBytes(buf, sizeof(buf));

    bleuart.write(buf, count);
  }

  // Forward from BLEUART to HW Serial
  while (bleuart.available())
  {
    uint8_t ch;
    ch = (uint8_t)bleuart.read();
    Serial.write(ch);
  }
}
