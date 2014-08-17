/*
 * GPSTZTest.ino
 *
 * Created: 8/16/2014 1:23:20 PM
 * Author: Ryan
 */ 
#include <GPSTimeZoneLookup.h>

GPSTimeZoneLookup myGPSTZ(33.9612895,-111.3380113);

void setup()
{
    Serial.begin(115200);
    Serial.print("lat/long: ");
    Serial.print(myGPSTZ.latitude);
    Serial.print(myGPSTZ.longitude);
    Serial.print(" GMT Offset: ");
    Serial.print(myGPSTZ.GMTOffset);
    Serial.print(" Implements DST: ");
    Serial.println(myGPSTZ.implementsDST);
}

void loop()
{
}
