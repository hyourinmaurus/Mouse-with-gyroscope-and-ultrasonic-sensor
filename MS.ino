#include <Wire.h>
#include <Mouse.h>


int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
const int trig = 5;

const int echo = 6;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();

  pinMode(trig, OUTPUT); // Sets the trigPin as an Output
pinMode(echo, INPUT);
}

void loop() {
  recordAccelRegisters();

  recordGyroRegisters();

  //Serial.println(gx);
  vx = (gy + 180) / 200; //-180 offset
  vy = -(gx - 5300) / 200; // 5300 offset

  Mouse.move(vx, vy);
 digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
 delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  

 Serial.println(distance);
  if (distance < 5) {
    Mouse.click();
  }
  }
  void setupMPU(){

  Wire.beginTransmission(0b1101000); 

  Wire.write(0x6B); 

  Wire.write(0b00000000); 

  Wire.endTransmission();  

  Wire.beginTransmission(0b1101000); //I2C address of the MPU

  Wire.write(0x1B); 

  Wire.write(0x00000011); //Setting the gyro to full scale +/- 500deg./s 

  Wire.endTransmission(); 

  Wire.beginTransmission(0b1101000); //I2C address of the MPU

  Wire.write(0x1C); 

  Wire.write(0b00001000); //Setting the accel to +/- 8g

  Wire.endTransmission(); 

}



void recordAccelRegisters() {

  Wire.beginTransmission(0b1101000); //I2C address of the MPU

  Wire.write(0x3B); //Starting register for Accel Readings

  Wire.endTransmission();

  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)

  while(Wire.available() < 6);

  ax = Wire.read()<<8|Wire.read(); //get ax

  ay = Wire.read()<<8|Wire.read(); //get ay

  az = Wire.read()<<8|Wire.read(); //get az



}







void recordGyroRegisters() {

  Wire.beginTransmission(0b1101000); //I2C address of the MPU

  Wire.write(0x43); //Starting register for Gyro Readings

  Wire.endTransmission();

  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)

  while(Wire.available() < 6);

  gx = Wire.read()<<8|Wire.read(); //get gx

  gy = Wire.read()<<8|Wire.read(); //get gy

  gz = Wire.read()<<8|Wire.read(); //get gz

}







