#pragma once

#include <stddef.h>

#include <Arduino.h>
#include <FastLED.h>
#include <crgb.h>
#include <Definitions.h>

#include <ArxContainer.h> // Make sure to include this after Definitions.h


class LedStrip {
    public:
        LedStrip(const size_t pin, size_t size, uint8_t brightness = 10) : ledNum_(size) {
            leds_ = new CRGB[size];
            assignLeds(pin);
            FastLED.setDither(false);
            FastLED.setCorrection(TypicalLEDStrip);
            FastLED.setBrightness(brightness);
            FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);
            fill_solid(leds_, size, CRGB::Black);
            FastLED.delay(500);            
            // FastLED.show(0);
        }
        ~LedStrip() {}
        bool mapValues(std::deque<uint32_t> values);
        bool shiftColorsUp(size_t increment = 1, bool show = true);
        bool setLed(size_t led, uint32_t color, bool show = true);
        bool setLed(size_t led, CRGB color, bool show = true);
        bool colorWipe(CRGB color, uint16_t wait);
        bool colorWipeReverse(CRGB color, uint16_t wait);
        bool clearLeds();
        bool startupSequence();  
    private:
        void assignLeds(const size_t pin);
        uint32_t computeAverage(const std::deque<uint32_t>& values, size_t start, size_t end);
        uint32_t getHexColorVal(uint32_t color);
        size_t pin_;
        size_t ledNum_;
        CRGB* leds_;
};