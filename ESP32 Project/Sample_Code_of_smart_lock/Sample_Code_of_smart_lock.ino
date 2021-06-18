#include "BluetoothSerial.h"
#include <ESP32Servo.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
long randNumber;
long pwd;
const int sled1 = 12;
const int sled2 = 13;
const int servoPin = 14;
long auth = 1234;
long n;
Servo myservo;
BluetoothSerial SerialBT;

void setup() 
{
  Serial.begin(115200);
  SerialBT.begin("Smart_Door_Lock");

  myservo.attach(14);                                           // Attaching servo motor to pin 14
  pinMode(sled1,HIGH);                                          // Turning on status led 1
  pinMode(sled2,HIGH);                                          // Turning on status led 2 
  randomSeed(analogRead(0));                                    // if analog input pin 0 is unconnected, random analog noise will cause the call to randomSeed() to generate different seed numbers each time the sketch runs. randomSeed() will then shuffle the random function.                                                                                                                                
}

void loop() 
{
  for ( int j = 1 ; j < 2 ; j++)
  {
    Authorise();
  while (SerialBT.available() == 0)
  {
  SerialBT.println("OTP Generated!");
  for (int counter = 1; counter < 2; counter++) 
  {   
  randNumber = random(1000,9999);                               // print a random number from 1000 to 9999
  SerialBT.println(randNumber);
  }
  delay(6000);
  }
  }
   OTPcheck();
   delay(10000);
}
void OTPcheck()
{
  while(SerialBT.available() == true)
  {
    
  }
  pwd = SerialBT.parseInt();
  if (pwd == randNumber)
  {
    SerialBT.println("Correct! Access Granted!");
    myservo.write(120); 
    digitalWrite(sled2,HIGH);
    digitalWrite(sled1,LOW);
  }
  else if (pwd != randNumber)
  {
    SerialBT.println("Try Again!");
    myservo.write(50); 
    digitalWrite(sled2,LOW);
    digitalWrite(sled1,HIGH);
  }

}
void Authorise()
{
  SerialBT.println("Please enter the password");
  for(int i = 1 ; i < 2 ; i++)
  {
    while(SerialBT.available() == true)
  {
    
  }
  n = SerialBT.parseInt();
  if ( n == auth)
  {
    SerialBT.println("Password correct");
    SerialBT.println("Pairing Done!");
  }
  else
  {
    SerialBT.println("Enter Valid Password!");
  }
  }
  
}
