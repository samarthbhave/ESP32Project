#include "BluetoothSerial.h"
int OTP1 = 0511;
int OTP;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()==0) {
   while(Serial.available()==0){
         
   }
   OTP = Serial.parseInt();
   if(OTP == OTP1){
    Serial.println("Unlocked");
   }
   else if (OTP =! OTP1){
    Serial.println("Retry Again");
   }
   delay(2000);
  }
  
  delay(20);
}
