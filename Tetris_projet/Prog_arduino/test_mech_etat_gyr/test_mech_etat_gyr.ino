#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int cas;

int Sp=12000;
int Sn=-12000;
int idState=0;
bool flag=true;
bool testp,testn,testx;
float xt=0;

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:

  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

  if (rawAccel.XAxis>=Sp){
        testp=true;
    }
    else{
        testp= false;
    }
    if (rawAccel.XAxis<=Sn){
        testn=true;
    }
    else{
        testn= false;
    }

   if (rawAccel.XAxis<xt){
        testx=true;
    }
    else{
        testx= false;
    }
    if (idState==0){
        if (testp==true){
            idState=1;
            cas = 1;
        }
        else if (testn==true){
            idState=3;
            cas=2;
        }
    }
    else if (idState==1){
        if (testx==true){
            idState=2;
            cas=0;

        }
    }
    else if (idState==2){
         if (testp==false){
            idState=0;
            cas=0;
            
         }
    }
    if (idState==0){
        if (testp==true){
            idState=1;
            cas=1;
        }
    }
    else if (idState==1){
        if (testx==true){
            idState=2;
            cas=0;
        }
    }
    else if( idState==2){
         if (testp==false){
            idState=0;
            cas=0;
         }
    }
    else if (idState==3){
        if (testx==false){
            idState=4;
            cas=0;

        }
    }
    else if (idState==4){
        if (testn==false){
            idState= 0;
            cas=0;
        }
    }
    xt=rawAccel.XAxis;


   /*if(rawAccel.XAxis >10000){
      cas=1;
    }

   else if(rawAccel.XAxis <-10000){
      cas=2;
    }*/
  
  switch(cas){
    case 0:
      break;
    case 1:
      Serial.println("left");
      break;
    case 2:
      Serial.println("right");
      break;
  }
  delay(42);
}
