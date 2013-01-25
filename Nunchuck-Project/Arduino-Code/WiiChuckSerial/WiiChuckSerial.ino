/*
   WiichuckSerial
 
   Uses Nunchuck Library to send nunchuck data to Processing
   
   originally created by Michael Margolis
   nunchuck adapter created by Tod E. Kurt
   
   code modified by Quin (Qtechknow)
   made on 22 Jan 13
 */


#include <Wire.h>
#include "Nunchuck.h"

// values to add to the sensor to get zero reading when centered
int offsetX, offsetY, offsetZ; 

void setup()
{
    Serial.begin(57600);
    nunchuckSetPowerpins();
    nunchuckInit(); // send the initialization handshake
    nunchuckRead(); // ignore the first time
    delay(50);
}
void loop()
{
  nunchuckRead();
  delay(6);
  boolean btnC = nunchuckGetValue(wii_btnC);
  boolean btnZ = nunchuckGetValue(wii_btnZ);
  
  if(btnC) {
    offsetX = 127 - nunchuckGetValue(wii_accelX) ; 
    offsetY = 127 - nunchuckGetValue(wii_accelY) ;         
  }
  Serial.print("Data,");
  printAccel(nunchuckGetValue(wii_accelX),offsetX) ; 
  printAccel(nunchuckGetValue(wii_accelY),offsetY) ; 
  printButton(nunchuckGetValue(wii_btnZ));      

  Serial.println();
}
     
void printAccel(int value, int offset)
{
  Serial.print(adjReading(value, 127-50, 127+50, offset));
  Serial.print(",");
}

void printJoy(int value)
{
  Serial.print(adjReading(value,0, 255, 0));
  Serial.print(",");
}

void printButton(int value)
{
  if( value != 0)
     value = 127;
  Serial.print(value,DEC);
  Serial.print(",");
}

int adjReading( int value, int min, int max, int offset)
{
   value = constrain(value + offset, min, max);
   value = map(value, min, max, -127, 127);
   return value;  
}
