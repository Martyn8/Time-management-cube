#include "NeoPixel\neoPixel.h"

Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void neoPixelShow(String activeWall)
{
    if (activeWall == "undefined")
    {
        NeoPixel.setPixelColor(0, 255, 0, 0, 0); //czerwony
        NeoPixel.setBrightness(20);
        NeoPixel.show();
    }
    else
    {
        if (activeWall == "1")
            NeoPixel.setPixelColor(0, 0, 0, 255, 0); //niebieski
        else if (activeWall == "3")
            NeoPixel.setPixelColor(0, 0, 255, 0, 0); //zielony
        else if (activeWall == "2")
            NeoPixel.setPixelColor(0, 0, 255, 255, 0); //cyjan
        else if (activeWall == "4")
            NeoPixel.setPixelColor(0, 255, 255, 0, 0); //żółty
        else if (activeWall == "S")
            NeoPixel.setPixelColor(0, 255, 255, 255, 0); //biały
        else if (activeWall == "5")
            NeoPixel.setPixelColor(0, 255, 0, 255, 0); //magenta
        else
            NeoPixel.setPixelColor(0, 255, 0, 0, 0); //czerwony

        NeoPixel.setBrightness(20);
        NeoPixel.show();
        delay(2000);
        NeoPixel.clear();
        NeoPixel.show();
    }
}