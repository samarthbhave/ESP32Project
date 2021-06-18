#include "BluetoothSerial.h"
#include <ESP32Servo.h>
Servo myservo;
int servoPin = 14;
String deviceid;
long pwd;
long randnumber;
int n;

int sled1=12;
int sled2=13;
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("OTPDude"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  SerialBT.println("OTP will be sent shortly");
  myservo.attach(14); 
  pinMode(sled1,1);
  pinMode(sled2,1);
  randomSeed(analogRead(0));
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  while(n=1){
  randnumber = random(1000,9999);
  Serial.println(randnumber);
  SerialBT.write(randnumber);
  delay(5000);
  }
  }
   digitalWrite(sled1,1);

check();

}


void check(){
  while (Serial.available());
 pwd = Serial.read(); 
 
if (pwd == randnumber ){
  SerialBT.println ("unlocked");
  myservo.write(120); 
  digitalWrite(sled2,1);
  digitalWrite(sled1,0);
}
if (pwd != randnumber ){
  SerialBT.println ("reset try again");
  myservo.write(50); 
  digitalWrite(sled2,0);
  digitalWrite(sled1,1);
} 
  
}

  
