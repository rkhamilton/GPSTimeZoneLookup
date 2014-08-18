GPSTimeZoneLookup
=================
https://github.com/rkhamilton/GPSTimeZoneLookup

Ryan Hamilton
August 2014

This Arduino library performs local time zone lookups based on GPS coordinates for locations in the United States. Given a latitude / longitude coordinate, the library identifies the time zone, and whether that time zone respects daylight savings time. I show an example below of how this can be used in combination with the [Timezone library](https://github.com/JChristensen/Timezone) to calculate local time from UTC.

The library determines the time zone based on finding the closest populated location in it's know data set. If your coordinates are close to the edge of a time zone transition then the results may be incorrect. I couldn't think of a perfectly accurate solution to this problem that would fit into the memory of an Arduino. Suggestions are welcome!

#Acknowledgements
* The data source for the determination is based on the geonames.org database of populated US cities (cities15000.txt). 
* The distance calculation used to find the closest geonames location is taken from the [TinyGPSPlus library](http://arduiniana.org/libraries/tinygpsplus/).
* The [Flash](http://arduiniana.org/libraries/flash/) library is used to keep the memory requirements down. As of August 17, 2014 the current version of Flash (version 5) does not compile using Arduino 1.5.7. I forked the library and applied some patches that were posted on the comments of the author's site (I take no credit!) and the revised library compiles and seems to work properly.

# Usage

```Arduino
#include <Timezone.h>
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