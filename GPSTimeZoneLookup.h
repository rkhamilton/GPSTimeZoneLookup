/*
  GPSTimeZoneLookup.h - Library for looking up time zones from latitude and longitude.
  Created by Ryan Hamilton, June 18 2014.
  Released into the public domain.
*/

#ifndef GPSTimeZoneLookup_h
#define GPSTimeZoneLookup_h

#include <Arduino.h>

class GPSTimeZoneLookup
{
  public:
    GPSTimeZoneLookup(float myLat, float myLong);
	int GMTOffset;
	bool implementsDST;
    float latitude;
    float longitude;
  private:
    double distanceBetween(double lat1, double long1, double lat2, double long2);
    void findClosestCity();
	float _closestCityLat;
	float _closestCityLong;
	float _closestCityDistance;
	float _closestCityUsesDST;
	float _closestCityGMTOffset;
};

#endif
