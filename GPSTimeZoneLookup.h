/*
  GPSTimeZoneLookup.h - Library for looking up time zones from latitude and longitude.
  Created by Ryan Hamilton, June 18 2014.
  Released into the public domain.
*/

#ifndef GPSTimeZoneLookup
#define GPSTimeZoneLookup

#include <Arduino.h>
#include <TinyGPS++.h>

class GPSTimeZoneLookup
{
  public:
    GPSTimeZoneLookup(float lat, float long);
	int GMTOffset;
	bool implementsDST;
  private:
	float _closestCityLat;
	float _closestCityLong;
	float _closestCityDistance = 3.0E+38; //very large distance, any point on earth will be closer
	float _closestCityUsesDST;
	float _closestCityGMTOffset;
}

#endif
