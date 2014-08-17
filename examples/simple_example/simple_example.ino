/*
 * GPSTZTest.ino
 *
 * Created: 8/16/2014 1:23:20 PM
 * Author: Ryan
 */ 
#include <GPSTimeZoneLookup.h>

void setup()
{
  Serial.begin(115200);
  // Arizona, offset -7, no DST
  GPSTimeZoneLookup tz1(33.9612895,-111.3380113);
  printResults(tz1);
  // San Francisco, offset -8, uses DST
  GPSTimeZoneLookup tz2(37.6811162,-122.4176873);
  printResults(tz2);
}

void loop()
{
}

void printResults(GPSTimeZoneLookup me)
{
  Serial.print("lat/long: ");
  Serial.print(me.latitude);
  Serial.print(", ");
  Serial.print(me.longitude);
  Serial.print(" GMT Offset: ");
  Serial.print(me.GMTOffset);
  Serial.print(" Implements DST: ");
  Serial.println(me.implementsDST);
}
