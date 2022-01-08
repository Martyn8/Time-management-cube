#include "NeoPixel\neoPixel.h"

Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void neoPixelShow(String activeWall)
{
    if (activeWall == "undefined")
    {
        NeoPixel.setPixelColor(0, 255, 0, 0, 0); //czerwony
        NeoPixel.setBrightness(20);
        NeoPixel.show();
        delay(2000);
    }
    else
    {
        if (activeWall == "1")
        {
            NeoPixel.setPixelColor(0, 0, 0, 255, 0); //niebieski
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }
        else if (activeWall == "3")
        {

            NeoPixel.setPixelColor(0, 0, 255, 0, 0); //zielony
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }
        else if (activeWall == "2")
        {
            NeoPixel.setPixelColor(0, 0, 255, 255, 0); //seledynowy
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }
        else if (activeWall == "4")
        {

            NeoPixel.setPixelColor(0, 255, 255, 0, 0); //żółty
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }
        else if (activeWall == "S")
        {

            NeoPixel.setPixelColor(0, 255, 255, 255, 0); //biały
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }
        else if (activeWall == "5")
        {
            NeoPixel.setPixelColor(0, 255, 0, 255, 0); //fioletowy
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }
        else
        {
            NeoPixel.setPixelColor(0, 255, 0, 0, 0); //czerwony
            NeoPixel.setBrightness(20);
            NeoPixel.show();
            delay(2000);
        }

        // NeoPixel.setPixelColor(0, 255, 128, 0, 0); //pomarańczowy
        // NeoPixel.setBrightness(20);
        // NeoPixel.show();
        // delay(2000);

        NeoPixel.clear();
        NeoPixel.show();
    }
}