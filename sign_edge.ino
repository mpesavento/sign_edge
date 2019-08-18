#include "FastLED.h"

#define NUM_LEDS 102
#define DATA_PIN 9
#define CLOCK_PIN 8
#define CHIPSET APA102
#define COLOR_ORDER BGR

#define FRAMES_PER_SECOND  30

CRGB leds[NUM_LEDS];

#define BASE_BRIGHTNESS 100


void setup() {
  Serial.println("resetting");
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER, DATA_RATE_MHZ(1)>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( 150 );

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
    static uint8_t dval = 16; //8;
    static uint8_t num = 5;
    static uint8_t fade = 10;
    

    // colored dots sweeping back and forth, with fading trails
    fadeToBlackBy( leds, NUM_LEDS, fade);
    int pos = 0;
    for (int i = 0; i < num; i++) {
      pos = beatsin16(num-i+1, 0, NUM_LEDS);
      leds[pos] += CHSV( hue+(i*dhue), 255-i*dsat, 196-i*dval);
    }
    
    hue++;
    return 0;
} 

void loop() {
  sinelonN();
//  rainbow();

//  // black out the LEDs on the side
//  for (int i=42; i <42+9; i++) {
//    leds[i] = CRGB::Black;
//  }
  
  FastLED.delay(1000 / FRAMES_PER_SECOND);
  
}
