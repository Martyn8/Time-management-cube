#ifndef pixel_h
#define pixel_h

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

extern Adafruit_NeoPixel NeoPixel;

void neoPixelShow(String activeWall);

#endif