#include <LedStrip.h>
#include <OneButton.h>

#include <Log.h>

volatile size_t ledNum;
volatile bool shifting; 

LedStrip* strip;
OneButton btn(BUTTON);

static void shiftColors() {
  shifting = true;
}

static void stopShifting() {
  Log::LOG_I("Stop Shifting");
  shifting = false;
}

static void singleClick() {
  Log::LOG_I("Single Click!");
  if (ledNum == 1) {
    strip->mapValues({CRGB::Green, CRGB::Red});
  } else if (ledNum == 2) {
    strip->mapValues({CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::Yellow});
  } else if (ledNum == 3) {
    strip->mapValues({CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::Yellow, CRGB::Amethyst, CRGB::Crimson});
  } else if (ledNum == 4) {
    strip->mapValues({CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::Yellow, CRGB::Amethyst, CRGB::Crimson, CRGB::DarkGreen, CRGB::Pink, CRGB::Gold});
  } else if (ledNum == 5) {
    strip->clearLeds();
    ledNum = 0;
  }
  ledNum++;
}

void setup() {
  Log::setLogLevel(level::Debug);

  strip = new LedStrip(LED_STRIP, LED_NUMBER, BRIGHTNESS);
  strip->startupSequence();

  btn.attachClick(singleClick);
  btn.attachDuringLongPress(shiftColors);
  btn.attachLongPressStop(stopShifting);
  ledNum = 1;

  Log::LOG_I("Setup complete! Starting now...");
}

void loop() {
  btn.tick();
  if (shifting) {
    strip->shiftColorsUp(1, true);
    FastLED.show();
  }
}
