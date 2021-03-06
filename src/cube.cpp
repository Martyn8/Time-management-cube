#include <Arduino.h>

#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

#include <Adafruit_Sensor.h>

//#include <SPI.h>
//#include <Adafruit_FRAM_SPI.h>

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
#define SLEEPING_DELAY 5000

/********************************************************Send data**************************************************************/

void sendDataToDevice()
{

  Serial.println("\n");
  String readDate = framReadDate();
  Serial.println("Date: " + readDate + "\n");

  String readTime = framReadActStart();
  Serial.println("Time: " + readTime + "\n");

  String readDur = framReadDuration();
  Serial.println("Duration: " + readDur + "\n");

  String timestamp = readDate + " " + readTime;

  //int count = Serial.readBytes(buf, sizeof(buf));
  //bleuart.write( buf, count );

  char charBuf[20];
  activeWall.toCharArray(charBuf, 20);

  bleuart.write(charBuf);

  timestamp.toCharArray(charBuf, 20);

  bleuart.write(charBuf);

  readDur.toCharArray(charBuf, 20);

  bleuart.write(charBuf);

  Serial.println("data has been sent");
}

/******************************************************SLEEP******************************************************************/
/*
  Function responsible for putting cube in system off mode;
*/
void sleep(unsigned long time)
{
  Serial.println(" going to sleep in 5 s ");
  activeWall = "S";
  while (accel_z > 9)
  {

    //    if ((millis() - lastTime) > accelReadDelay) {
    //      Serial.println(" in while ");
    accelRead();

    //      lastTime = millis();
    //    }

    // shutdown when time reaches SLEEPING_DELAY ms
    if (((millis() - time) > SLEEPING_DELAY))
    {
      Serial.println(" go zzz");
      delay(100);

      // to reduce power consumption when sleeping, turn off all your LEDs (and other power hungry devices)
      digitalWrite(LED_BUILTIN, LOW);
      //Bluefruit.autoConnLed(false);
      // setup your wake-up pins.
      //pinMode(WAKE_LOW_PIN,  INPUT_PULLUP_SENSE);
      pinMode(WAKE_HIGH_PIN, INPUT_PULLDOWN_SENSE);

      calculateTime();
      activeWall = "";

      //      framWriteDate();
      //      framWriteActStart();
      //      framWriteDuration();
      writeDataToFram(startOfActDate, startOfActTime, activityDuration);

      delay(1000);
      Serial.println(startOfActDate + "\n");
      Serial.println(startOfActTime + "\n");
      char buff[] = "hh:mm:ss";
      Serial.println(activityDuration.toString(buff));

      //showFram();

      showFram();

      Serial.println("\n");
      String readDate = framReadDate();
      Serial.println("Date: " + readDate + "\n");

      String readTime = framReadActStart();
      Serial.println("Time: " + readTime + "\n");

      String readDur = framReadDuration();
      Serial.println("Duration: " + readDur + "\n");

      //       Serial.println("wczytany string z pami??ci \n");
      //
      //       String s = framReadDate(addr);
      //
      //       Serial.println(s);

      /*
         this function puts the whole nRF52 to deep sleep (no Bluetooth).
         If no sense pins are setup (or other hardware interrupts), the nrf52 will not wake up.
      */
      delay(300);

      sd_power_system_off(); // power down nrf52
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
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_x < -9)
  {
    activeWall = "3";
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_y > 9)
  {
    activeWall = "2";
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_y < -9)
  {
    activeWall = "4";
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else if (accel_z > 9)
  {
    activeWall = "S";
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
    sleep(millis()); // call millis() and pass it to the sleep function.  On wake-up, millis will start at 0 again.
  }
  else if (accel_z < -9)
  {
    activeWall = "5";
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays on wall " + activeWall + "\n");
  }
  else
  {
    activeWall = "undefined";
    neoPixelShow(activeWall);
    Serial.println("\nThe cube lays in an " + activeWall + " position\n");
  }
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

  // Set up and start advertising
  //  BLESetUp();
  //  startAdv();
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
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);

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

  if (!rtc.isrunning())
  {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //FRAM setup
  if (fram.begin())
  {
    Serial.println("Found SPI FRAM");
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
    Serial.println(" Motion detected ");
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);

    delay(2000);

    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1500);

    accelRead();

    if (activeWall.length() == 0)
    {
      //if cube was asleep
      //set activeWall for the first time and start counting or go to sleep
      setActiveWall();
      delay(100);
      startCounting();
    }
    else
    {
      //if cube was active but wall was changed
      //check if wall is the same as previous
      String previousWall = activeWall;
      setActiveWall();
      delay(100);
      if (activeWall != previousWall /*&& (previousWall != "S")*/)
      {
        //if activeWall is the same as previous continue counting
        //if not save current data and start counting again or go to sleep

        calculateTime();
        writeDataToFram(startOfActDate, startOfActTime, activityDuration);
        sendDataToDevice();
        startCounting();
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
