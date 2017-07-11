#include "FastLED.h"

#define NUM_LEDS 93
#define DATA_PIN 11
#define CHIPSET WS2812B
#define COLOR_ORDER GRB  // WS2812B order

#define FRAMES_PER_SECOND  30

CRGB leds[NUM_LEDS];


void setup() {
  delay(2000);
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  FastLED.setBrightness(50);
}

void rainbow() {
  static int offset = 0;
  fill_rainbow(leds, NUM_LEDS, offset, 7);
  offset++;
}

int sinelonN() {
    static uint8_t hue = 0;
    static uint8_t dhue = 32;
    static uint8_t dsat = 1;
    static uint8_t dval = 8; //16;
    static uint8_t num = 5;
    static uint8_t fade = 10;
    

    // colored dots sweeping back and forth, with fading trails
    fadeToBlackBy( leds, NUM_LEDS, fade);
    int pos = 0;
    for (int i = 0; i < num; i++) {
      pos = beatsin16(num-i+1,0,NUM_LEDS);
      leds[pos] += CHSV( hue+(i*dhue), 255-i*dsat, 196-i*dval);
    }
    
    hue++;
    return 0;
} 

void loop() {
  sinelonN();

  // black out the LEDs on the side
  for (int i=42; i <42+9; i++) {
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

}
