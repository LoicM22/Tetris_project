#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    64



CRGB leds[NUM_LEDS];
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}
void loop() {
  /*for(int i=0;i<64;i++){
    leds[i] = CRGB(0, 0, 10);
    FastLED.show();
    
  }*/
  
  /*leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(500);  
  
  delay(500);
  leds[2] = CRGB(0, 0, 255);
  FastLED.show();
  leds[5] = CRGB(150, 0, 255);
  FastLED.show();
  leds[9] = CRGB(255, 200, 20);
  FastLED.show();
  delay(500);
  
  delay(500);
  
  delay(500);
  leds[14] = CRGB(85, 60, 180);
  FastLED.show();
  delay(500);
  leds[19] = CRGB(50, 255, 20);
  FastLED.show();
  delay(500);*/
  int i=0;
  while (i<9){
    leds[i] = CRGB(0, 0, 255);
    leds[i+8] = CRGB(0, 0, 255);
    leds[i+16] = CRGB(0, 0, 255);
    leds[i+24] = CRGB(0, 0, 255);
    leds[i+32] = CRGB(0, 0, 255);
    leds[i+40] = CRGB(0, 0, 255);
    leds[i+48] = CRGB(0, 0, 255);
    leds[i+56] = CRGB(0, 0, 255);
    if(i>0){
          leds[i-1]=CRGB(0, 0, 0);
          leds[i+7]=CRGB(0, 0, 0);
          leds[i+15]=CRGB(0, 0, 0);
          leds[i+23]=CRGB(0, 0, 0);
          leds[i+31]=CRGB(0, 0, 0);
          leds[i+39]=CRGB(0, 0, 0);
          leds[i+47]=CRGB(0, 0, 0);
          leds[i+55]=CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(42);
    i++;    
  }
}
