#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    64
#include <Wire.h>
#include <MPU6050.h>

int i=0;
CRGB leds[NUM_LEDS];

MPU6050 mpu;

int cas;

int xcas;
int Sp = 4;
int Sn = -4;
int idState=0;
bool flag = true;
bool testp,testn;
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
    checkSettings();

}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}

void loop() {
  
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
    Vector rawAccel = mpu.readRawAccel();
    Vector normAccel = mpu.readNormalizeAccel();
  
    //Serial.println(normAccel.XAxis);
    //Serial.println(normAccel.YAxis);
    //Serial.println(normAccel.ZAxis);


    
    if(normAccel.ZAxis > 18){
      cas = 1;
    }
    else if(normAccel.YAxis < -7){
      cas= 2;
    }
    
    else if(rawAccel.XAxis >15000){
      cas=5;
    }

    else if(rawAccel.XAxis <-15000){
      cas=6;
    }
    
    if (normAccel.XAxis>=Sp){
        testp=true;
    }
    else{
        testp= false;
    }
    if (normAccel.XAxis<=Sn){
        testn=true;
    }
    else{
        testn= false;
    }
    if (idState==0){
        if (testp==true){
            idState=1;
            cas = 3;
        }
        else if (testn==true){
            idState=3;
            cas=4;
        }
    }
    else if (idState==1){
        if (testn==true){
            idState=2;
        }
    }
    else if (idState==2){
         if (testn==false){
            idState=0;
         }
    }
    if (idState==0){
        if (testp==true){
            idState=1;
        }
    }
    else if (idState==1){
        if (testn==true){
            idState=2;
        }
    }
    else if( idState==2){
         if (testn==false){
            idState=0;
         }
    }
    else if (idState==3){
        if (testp==true){
            idState=4;
        }
    }
    else if (idState==4){
        if (testp==false){
            idState= 0;
        }
    }


    else if(rawAccel.XAxis >10000){
      cas=5;
    }

    else if(rawAccel.XAxis <-10000){
      cas=6;
    }
    
    switch(cas){
    case 0:
      break;
    case 1:
      Serial.println("down");
      break;
    case 2:
      Serial.println("pause");
      break;
    case 3:
      Serial.println("right");
      break;
    case 4:
      Serial.println("left");
      break;
    case 5:
      Serial.println("turn left");
      break;
    case 6:
      Serial.println("turn right");
      break;
  }
  cas=0;
    delay(42);
    i++;
  }
}
