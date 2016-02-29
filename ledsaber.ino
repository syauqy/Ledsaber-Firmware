// This #include statement was automatically added by the Particle IDE.
#include "MPU6050.h"

int ledRPin = D3;
int ledGPin = WKP;
int ledBPin = D2;

String mpu = "{\"x\":\"0\",\"y\":\"0\",\"z\":\"0\"}";
String rgb = "{\"r\":\"0\",\"g\":\"255\",\"b\":\"255\"}";

void readMPU() {
  MPU6050();
  mpu = "{\"x\":\"" + String(get_last_x_angle(),2) + "\"," + 
         "\"y\":\"" + String(get_last_y_angle(),2) + "\"," + 
         "\"z\":\"" + String(get_last_z_angle(),2) + "\"}";
}

Timer MPU6050_task(20, readMPU);

void setup() {
  Wire.begin();

  MPU6050_init();
  MPU6050_task.start();
  
  RGB.control(true);
  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);
  setRGB("0,255,255");
  
  Particle.variable("mpu", mpu);
  Particle.variable("rgb", rgb);
  Particle.function("setrgb", setRGB);
}

void loop() {
  
}

int setRGB(String command) {
  int commaIndex[2];    

  if(command == "")
    return -1;
    
  commaIndex[0] = command.indexOf(',');
  for(int i = 1; i < 2; i++)
  {
    commaIndex[i] = command.indexOf(',', commaIndex[i-1] + 1);
    if(commaIndex[i] == -1)
      return -1;
  }
  
  int r = (command.substring(0, commaIndex[0])).toInt();
  int g = (command.substring(commaIndex[0] + 1, commaIndex[1])).toInt();
  int b = (command.substring(commaIndex[1] + 1)).toInt();
  
  RGB.color(r, g, b);
  analogWrite(ledRPin, 255-r);
  analogWrite(ledGPin, 255-g);
  analogWrite(ledBPin, 255-b);
  
  rgb = "{\"r\":\"" + String(r) + "\"," + 
         "\"g\":\"" + String(g) + "\"," + 
         "\"b\":\"" + String(b) + "\"}";
  
  return 0;
}