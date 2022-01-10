#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// accelero left right
int cas;
int Sp = 6;
int Sn =-6;
int idState=0;
bool flag = true;
bool testp, testn;

//gyro
int etat=0;

int Spxh =16000;
int Sph =14000;
int Spb =5000;

int Snxh =-16000;
int Snh=-14000;
int Snb =-5000;

// accelero down
int state=0;

int Sdph = 8;
int Sdpb = 1;

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

  /*if(normAccel.ZAxis > 18){
    cas = 1;
  }
  else if(normAccel.YAxis < -7){
    cas= 2;
  }*/

  if(normAccel.XAxis >= Sp){
    testp = true;
  }
  else{
    testp=false;
  }
  if(normAccel.XAxis <= Sn){
    testn = true;
  }
  else{
    testn=false;
  }

  if (idState==0){
    if(testp==true){
      idState=1;
      cas=3;
    }
    else if(testn==true){
      idState=3;
      cas=4;
    }
  }
  else if(idState==1){
    if(testn==true){
      idState=2;
    }
  }
  else if(idState==2){
    if(testn == false){
      idState=0;
    }
  }
  if(idState==0){
    if(testp==true){
      idState=1;
      cas=3;
    }
  }
  else if(idState==1){
    if(testn==true){
      idState==2;
    }
  }
  else if(idState==2){
    if (testn==false){
      idState=0;
    }
  }
  else if(idState==3){
    if (testp==true){
      idState=4;
    }
  }
  else if(idState==4){
    if (testp==false){
      idState=0;
    }
  }


  //gyro

  if(etat==0){
    if((rawAccel.XAxis <= Spxh)&&(rawAccel.XAxis >= Sph)){
      etat=1;
      cas = 5;
    }
    else if((rawAccel.XAxis >= Snxh)&& (rawAccel.XAxis <= Snh)){
      etat = -1;
      cas = 6;
    }
  }
  else if(etat==1){
    etat=2;
  }
  else if(etat==2){
    if(rawAccel.XAxis <= Spb){
      etat=0;
    }
  }
  else if(etat==-1){
    etat=-2;
  }
  else if(etat==-2){
    if(rawAccel.XAxis >= Snb){
      etat=0;
    }
  }

  //down

  if(state==0){
    if(normAccel.ZAxis <= Sdpb){
      state=1;
      cas=1;
    }
  }
  else if(state==1){
    state=2;
  }
  else if(state==2){
    if(normAccel.ZAxis>=Sdph){
      state=0;
    }
  }

  
  switch(cas){
    case 0:
      break;
    case 1:
      Serial.println("down");
      break;
    /*case 2:
      Serial.println("pause");
      break;*/
    case 3:
      Serial.println("right");
      break;
    case 4:
      Serial.println("left");
      break;
    case 5:
      Serial.println("rot left");
      break;
    case 6:
      Serial.println("rot right");
      break;    
   }
   cas=0;
  
}
