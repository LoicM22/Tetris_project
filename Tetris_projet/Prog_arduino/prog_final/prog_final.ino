#include <FastLED.h>

  /* LED battery */

#define LED_PIN_1     6
#define NUM_LEDS_1    1

  /* LED cube */

#define LED_PIN_2    7
#define NUM_LEDS_2   60




CRGB leds_1[NUM_LEDS_1];
CRGB leds_2[NUM_LEDS_2];



void setup() {
  Serial.begin(115200);

  /* LED battery */
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS_1);

  /* LED cube */
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS_2);


}

void loop() {
  
  /* LED Battery */
  
  int resultBinary = analogRead(A0);
  float resultVolts = resultBinary / 1023.0 * 5.0;
  int R1 = 100;
  int R2 = 220;
  float tension = (resultVolts / R1 * (R1 + R2))-0.5;

  float pourc_volt = (tension/9.80)*100;
  
  if (pourc_volt > 80){
    leds_1[0] = CRGB(0, 4, 4);
    FastLED.show();
  }
  if ((pourc_volt>60) && (pourc_volt<80)){
    leds_1[0] = CRGB(0, 4, 0);
    FastLED.show(); 
  }
  if ((pourc_volt>40) && (pourc_volt<60)){
    leds_1[0] = CRGB(4, 4, 0);
    FastLED.show(); 
  }
  if ((pourc_volt>20) && (pourc_volt<40)){
    leds_1[0] = CRGB(4, 1, 0);
    FastLED.show(); 
  }
  if (pourc_volt<20){
    leds_1[0] = CRGB(4, 0, 0);
    FastLED.show();
  }  

  /* LED cube */

  int i=0;
  while (i<13){
    leds_2[i] = CRGB(0, 0, 255);
    leds_2[i+12] = CRGB(0, 0, 255);
    leds_2[i+24] = CRGB(0, 0, 255);
    leds_2[i+36] = CRGB(0, 0, 255);
    leds_2[i+48] = CRGB(0, 0, 255);
    if(i>0){
          leds_2[i-1]=CRGB(0, 0, 0);
          leds_2[i+11]=CRGB(0, 0, 0);
          leds_2[i+23]=CRGB(0, 0, 0);
          leds_2[i+35]=CRGB(0, 0, 0);
          leds_2[i+47]=CRGB(0, 0, 0);
    }
    FastLED.show();
    i++;
    delay(42);  
  }
}
