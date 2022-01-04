#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    64



CRGB leds[NUM_LEDS];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:

  leds[0] = CRGB(4, 0, 0);
  FastLED.show();
  leds[1] = CRGB(4, 1, 0);
  FastLED.show();
  leds[2] = CRGB(4, 4, 0);
  FastLED.show();
  leds[3] = CRGB(0, 4, 0);
  FastLED.show();
  delay(500);  

}
