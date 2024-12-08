#include <LedStrip.h>
#include <Log.h>


bool LedStrip::startupSequence() {
    colorWipe(CRGB::Red, 0);
    colorWipeReverse(CRGB::Red, 0);
    fill_rainbow_circular(leds_, ledNum_, 0, 80);
    FastLED.show();
    for (size_t i = 0; i < 600; i++) {
        LedStrip::shiftColorsUp(1, true);
    }
    return true;
}

bool LedStrip::shiftColorsUp(size_t increment, bool show) {
    // TODO: add support for incrementing
    CRGB savedLed;
    CRGB prevLed = leds_[0];
    for (size_t i = 1; i < ledNum_; i++) {
        savedLed = leds_[i];
        LedStrip::setLed(i, prevLed, false);
        prevLed = savedLed;
    }
    LedStrip::setLed(0, savedLed, show);
    return true;
}

bool LedStrip::mapValues(std::deque<uint32_t> values) {
    if (values.size() == ledNum_) {
        Log::LOG_D("Direct mapping since #values == #LEDS");
        for (size_t i = 0; i < ledNum_; i++) {
            setLed(i, values[i], false);
        }
    } else if (values.size() > ledNum_) {
        Log::LOG_D("Averaging mapping since #values > #LEDS"); // TODO: validate this...
        size_t segmentSize = values.size() / ledNum_;
         for (size_t i = 0; i < ledNum_; i++){
            // Determine the segment's range in dataPoints
            int startIdx = i * segmentSize;
            int endIdx = (i == ledNum_ - 1) ? values.size()-1 : (i + 1) * segmentSize;  // Make sure last segment includes all remaining elements
            // TODO: instead of computing average we probs want to pick the value that is most common in segment
            setLed(i, computeAverage(values, startIdx, endIdx), false);
         }
        
    } else {
        Log::LOG_D("Interpolating mapping since #value < #LEDS");
        size_t segmentSize = ledNum_ / values.size();
        size_t remainder = ledNum_ % values.size();
        size_t offset = 0;
        for (size_t i = 0; i < values.size(); i++) {
            size_t extra = 0;
            if (offset < remainder){
                extra = 1;
            }
            for (size_t j = 0; j < segmentSize + extra; j++) {
                setLed(j + i*segmentSize + offset, values[i], false);
            }
            if (extra == 1) {
                offset++;
            }
        }
    }
    FastLED.show();
    return true;
}

// Function to compute the average value of a segment
uint32_t LedStrip::computeAverage(const std::deque<uint32_t>& values, size_t start, size_t end) {
    Log::LOG_D("Computing average of segment size: ", end-start+1);
    int sum = 0;
    for (size_t i = start; i <= end; i++) {
        sum += values[i];
    }
    int avg = round(static_cast<double>(sum) / (end-start+1));
    Log::LOG_D("Avg: ", avg);
    return avg;
}

void LedStrip::assignLeds(const size_t pin) {
    if (pin == LED_STRIP) {
        FastLED.addLeds<WS2812B, LED_STRIP, GRB>(leds_, ledNum_); //WS2812 for other ones
    } else {
        Log::FATAL("Unsupported PIN assgined for LED Strip! Pin_", pin);
    }
}

bool LedStrip::clearLeds() {
    FastLED.clear(); // should we pass true into this function?
    FastLED.show();
    return true;
}

bool LedStrip::setLed(size_t led, uint32_t color, bool show) {
    return LedStrip::setLed(led, CRGB(color), show);
}

bool LedStrip::setLed(size_t led, CRGB color, bool show) {
    // Log::LOG_I("Assigning LED #", led % ledNum_);
    if (led >= ledNum_) {
        Log::FATAL("Tried to set out of bound led:", led);
    }
    leds_[led] = color;
    if (show) {
        FastLED.show();
    }
    return true;
}

bool LedStrip::colorWipe(CRGB color, uint16_t wait) {
  for (uint16_t i = 0; i < ledNum_; i++) {
    setLed(i, color, true);
    delay(wait);
    setLed(i, CRGB::Black, true);
  }
  return true;
}

bool LedStrip::colorWipeReverse(CRGB color, uint16_t wait) {
  for (uint16_t i = 0; i < ledNum_; i++) {
    setLed(ledNum_ - i - 1, color, true);
    delay(wait);
    setLed(ledNum_ - i - 1, CRGB::Black, true);
  }
  return true;
}