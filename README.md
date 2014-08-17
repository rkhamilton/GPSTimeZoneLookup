GPSTimeZoneLookup
=================
https://github.com/rkhamilton/GPSTimeZoneLookup

Ryan Hamilton
August 2014

This Arduino library performs local time zone lookups based on GPS coordinates for locations in the United States. Given a latitude / longitude coordinate, the library identifies the time zone, and whether that time zone respects daylight savings time. This can be used in combination with the Timezone library (https://github.com/JChristensen/Timezone) to calculate local time from UTC.  I have not tackled this problem for locations outside of the US. The database of coordinates that this method uses to identify the timezone would be too large to be practical for use on a microcontroller, so I restricted this initial scope to only the US.

There are two major caveats in this library.

1. The library determines the time zone based on finding the closest populated location in it's know data set. If your coordinates are close to the edge of a time zone transition then the results may be incorrect. I couldn't think of a perfectly accurate solution to this problem that would fit into the memory of an Arduino. Suggestions are welcome!
2. The arrays of GPS coordinates have been aggressively trimmed down to the minimal set that I could find to identify all US time zones. **However, there is a peak memory usage of 3.2 KB.** That will fit into an Arduino Mega 2560, but not into an Uno. I believe this could be rectified by clever use of PROGMEM, but I'm not sure how to do it. Help is welcome on this one too!

#Acknowledgements
* The data source for the determination is based on the geonames.org database of populated US cities (cities15000.txt). 
* The distance calculation used to find the closest geonames location is taken from the TinyGPSPlus library (http://arduiniana.org/libraries/tinygpsplus/).

# Usage

```Arduino
#include <Timezone.h> //https://github.com/JChristensen/Timezone
TimeChangeRule timeChangeRuleStart;
TimeChangeRule timeChangeRuleStop;

myTZ = GPSTimeZoneLookup(myLat,myLong);

switch(myTZ.GMTOffset){
        case -10: //Pacific/Honolulu
        Serial.println("US Hawaii?Aleutian Time Zone (Honolulu)");
        timeChangeRuleStart.week    = Second;
        timeChangeRuleStart.dow     = Sun;
        timeChangeRuleStart.month   = Mar;
        timeChangeRuleStart.hour    = 2;
        timeChangeRuleStart.offset  = -600;

        timeChangeRuleStop.week    = First;
        timeChangeRuleStop.dow     = Sun;
        timeChangeRuleStop.month   = Nov;
        timeChangeRuleStop.hour    = 2;
        timeChangeRuleStop.offset  = -600;
        break;
        case -9: //America/Anchorage
        Serial.println("US Alaska Time Zone (Anchorage)");
        timeChangeRuleStart.week    = Second;
        timeChangeRuleStart.dow     = Sun;
        timeChangeRuleStart.month   = Mar;
        timeChangeRuleStart.hour    = 2;
        timeChangeRuleStart.offset  = -480;

        timeChangeRuleStop.week    = First;
        timeChangeRuleStop.dow     = Sun;
        timeChangeRuleStop.month   = Nov;
        timeChangeRuleStop.hour    = 2;
        timeChangeRuleStop.offset  = -540;
        break;
        case -8: //America/Los_Angeles
        Serial.println("US Pacific Time Zone (Las Vegas, Los Angeles)");
        timeChangeRuleStart.week    = Second;
        timeChangeRuleStart.dow     = Sun;
        timeChangeRuleStart.month   = Mar;
        timeChangeRuleStart.hour    = 2;
        timeChangeRuleStart.offset  = -420;

        timeChangeRuleStop.week    = First;
        timeChangeRuleStop.dow     = Sun;
        timeChangeRuleStop.month   = Nov;
        timeChangeRuleStop.hour    = 2;
        timeChangeRuleStop.offset  = -480;
        break;
        case -7: //America/Phoenix or America/Denver
        if (myTZ.implementsDST) {
            Serial.println("US Mountain Time Zone (Denver, Salt Lake City)");
            timeChangeRuleStart.week    = Second;
            timeChangeRuleStart.dow     = Sun;
            timeChangeRuleStart.month   = Mar;
            timeChangeRuleStart.hour    = 2;
            timeChangeRuleStart.offset  = -360;

            timeChangeRuleStop.week    = First;
            timeChangeRuleStop.dow     = Sun;
            timeChangeRuleStop.month   = Nov;
            timeChangeRuleStop.hour    = 2;
            timeChangeRuleStop.offset  = -420;
        }
        else {
            Serial.println("Arizona is US Mountain Time Zone but does not use DST");
            timeChangeRuleStart.week    = Second;
            timeChangeRuleStart.dow     = Sun;
            timeChangeRuleStart.month   = Mar;
            timeChangeRuleStart.hour    = 2;
            timeChangeRuleStart.offset  = -420;

            timeChangeRuleStop.week    = First;
            timeChangeRuleStop.dow     = Sun;
            timeChangeRuleStop.month   = Nov;
            timeChangeRuleStop.hour    = 2;
            timeChangeRuleStop.offset  = -420;
        }
        break;
        case -6: //America/Chicago - US Central Time Zone (Chicago, Houston)
        Serial.println("US Central Time Zone (Chicago, Houston)");
        timeChangeRuleStart.week    = Second;
        timeChangeRuleStart.dow     = Sun;
        timeChangeRuleStart.month   = Mar;
        timeChangeRuleStart.hour    = 2;
        timeChangeRuleStart.offset  = -300;

        timeChangeRuleStop.week    = First;
        timeChangeRuleStop.dow     = Sun;
        timeChangeRuleStop.month   = Nov;
        timeChangeRuleStop.hour    = 2;
        timeChangeRuleStop.offset  = -360;
        break;
        case -5: //America/New_York
        Serial.println("US Eastern Time Zone (New York, Detroit)");
        timeChangeRuleStart.week    = Second;
        timeChangeRuleStart.dow     = Sun;
        timeChangeRuleStart.month   = Mar;
        timeChangeRuleStart.hour    = 2;
        timeChangeRuleStart.offset  = -240;

        timeChangeRuleStop.week    = First;
        timeChangeRuleStop.dow     = Sun;
        timeChangeRuleStop.month   = Nov;
        timeChangeRuleStop.hour    = 2;
        timeChangeRuleStop.offset  = -300;
        break;
        default:
        Serial.println("Not found! Offset from GMT outside range {-10 to -5}");
    }
	```