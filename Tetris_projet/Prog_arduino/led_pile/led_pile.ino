#include <FastLED.h>
#define LED_PIN     6
#define NUM_LEDS    64



CRGB leds[NUM_LEDS];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:
  int resultBinary = analogRead(A0);
  float resultVolts = resultBinary / 1023.0 * 5.0;
  int R1 = 100;
  int R2 = 220;
  float tension = (resultVolts / R1 * (R1 + R2))-0.5;

  float pourc_volt = (tension/9.80)*100;

  if (pourc_volt > 75){
    leds[0] = CRGB(0, 4, 0);
    FastLED.show();
  }
  if ((pourc_volt>40) && (pourc_volt<75)){
    leds[0] = CRGB(4, 4, 0);
    FastLED.show(); 
  }
  if (pourc_volt<40){
    leds[0] = CRGB(4, 0, 0);
    FastLED.show();
  }
  delay(500);  

}/*

void setup() {
  Serial.begin(9600);
}
void loop() {
  int resultBinary = analogRead(A0);
  float resultVolts = resultBinary / 1023.0 * 5.0;
  int R1 = 100;
  int R2 = 220;
  float tension = (resultVolts / R1 * (R1 + R2))-0.5;

  float pourc_volt = (tension/9.80)*100;
  Serial.print(tension);
  Serial.println(pourc_volt);
  
  delay(250);
}*/
 
