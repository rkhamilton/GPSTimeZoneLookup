/*
  GSPSlookup.cpp - Library for looking up time zones from latitude and longitude.
  Created by Ryan Hamilton, June 18 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "GPSTimeZoneLookup.h"
//#include <math.h>

GPSTimeZoneLookup::GPSTimeZoneLookup(float myLat, float myLong)
{
// find the city from the city list closest to our coordinates
    latitude = myLat;
    longitude = myLong;
    findClosestCity();
    // After all location parsing, write to the public properties
    GMTOffset = _closestCityGMTOffset;
    implementsDST = _closestCityUsesDST;
 }

void GPSTimeZoneLookup::findClosestCity()
{
        //define lat/long coordinates of all US citied above a population of 15000
        int _numCities = 313;
        int _minIndex = 0;
        double thisDistance;
        _closestCityDistance = 3.0E+38; //very large distance, any point on earth will be closer

        const float _cityCoords[313][2] = {
            {37.08339, -88.60005},
            {31.22323, -85.39049},
            {34.01426, -86.00664},
            {32.64541, -85.37828},
            {33.61427, -85.83496},
            {32.47098, -85.00077},
            {28.47688, -82.52546},
            {30.43826, -84.28073},
            {31.57851, -84.15574},
            {32.07239, -84.23269},
            {33.58011, -85.07661},
            {32.46098, -84.98771},
            {34.25704, -85.16467},
            {30.83658, -83.97878},
            {39.16532, -86.52639},
            {39.86671, -86.14165},
            {39.84338, -86.39777},
            {39.97837, -86.11804},
            {38.29674, -85.75996},
            {39.20144, -85.92138},
            {37.97476, -87.55585},
            {39.95559, -86.01387},
            {39.78504, -85.76942},
            {39.61366, -86.10665},
            {39.76838, -86.15804},
            {38.39144, -86.93111},
            {38.27757, -85.73718},
            {39.83865, -86.02526},
            {38.28562, -85.82413},
            {39.92894, -85.37025},
            {39.70421, -86.39944},
            {39.82894, -84.89024},
            {38.95922, -85.89025},
            {39.52144, -85.77692},
            {39.4667, -87.41391},
            {38.67727, -87.52863},
            {38.36446, -98.76481},
            {38.87918, -99.32677},
            {36.99032, -86.4436},
            {39.02756, -84.72411},
            {37.64563, -84.77217},
            {37.69395, -85.85913},
            {39.01673, -84.60078},
            {38.15979, -85.58774},
            {38.99895, -84.62661},
            {38.20091, -84.87328},
            {37.83615, -87.59001},
            {38.14285, -85.62413},
            {36.8656, -87.48862},
            {38.19424, -85.5644},
            {38.25424, -85.75941},
            {37.3281, -87.49889},
            {38.16007, -85.65968},
            {38.14118, -85.68774},
            {37.77422, -87.11333},
            {38.14535, -85.8583},
            {37.84035, -85.94913},
            {38.25285, -85.65579},
            {38.20007, -85.82274},
            {38.11118, -85.87024},
            {39.34589, -84.5605},
            {39.29034, -84.50411},
            {39.3995, -84.56134},
            {39.507, -84.74523},
            {39.21311, -84.59939},
            {35.04563, -85.30968},
            {36.16284, -85.50164},
            {34.99591, -85.15023},
            {35.06535, -85.24912},
            {35.01424, -85.2519},
            {36.38838, -86.44666},
            {36.20811, -86.2911},
            {36.50921, -86.885},
            {35.36202, -86.20943},
            {39.48061, -86.05499},
            {34.26759, -86.20887},
            {33.65983, -85.83163},
            {32.60986, -85.48078},
            {42.2942, -83.30993},
            {40.12448, -87.63002},
            {40.10532, -85.68025},
            {40.04115, -86.87445},
            {41.41698, -87.36531},
            {41.68199, -85.97667},
            {41.1306, -85.12886},
            {40.27948, -86.51084},
            {41.59337, -87.34643},
            {41.58227, -85.83444},
            {41.74813, -86.12569},
            {41.52837, -87.42365},
            {41.53226, -87.25504},
            {40.8831, -85.49748},
            {40.48643, -86.1336},
            {41.6106, -86.72252},
            {40.4167, -86.87529},
            {40.04837, -86.46917},
            {40.75448, -86.35667},
            {40.55837, -85.65914},
            {41.48281, -87.33281},
            {41.70754, -86.89503},
            {41.66199, -86.15862},
            {40.19338, -85.38636},
            {40.04559, -86.0086},
            {41.57587, -87.17615},
            {41.47892, -87.45476},
            {41.68338, -86.25001},
            {41.47309, -87.06114},
            {40.42587, -86.90807},
            {40.04282, -86.12749},
            {41.89755, -84.03717},
            {42.25754, -83.21104},
            {42.97225, -85.95365},
            {42.27756, -83.74088},
            {42.32115, -85.17971},
            {42.30865, -83.48216},
            {42.32226, -83.17631},
            {42.33698, -83.27326},
            {42.33143, -83.04575},
            {42.46059, -83.13465},
            {42.95947, -85.48975},
            {42.32559, -83.33104},
            {42.96336, -85.66809},
            {42.90975, -85.76309},
            {42.39282, -83.04964},
            {42.46254, -83.10409},
            {42.78752, -86.10893},
            {42.64059, -84.51525},
            {42.24587, -84.40135},
            {42.90725, -85.79198},
            {42.29171, -85.58723},
            {42.86947, -85.64475},
            {42.73254, -84.55553},
            {42.25059, -83.17854},
            {42.48587, -83.1052},
            {46.54354, -87.39542},
            {41.91643, -83.39771},
            {43.59781, -84.76751},
            {43.23418, -86.24839},
            {43.1689, -86.26395},
            {42.20115, -85.58},
            {42.22226, -83.3966},
            {42.67087, -83.03298},
            {42.21393, -83.19381},
            {42.58031, -83.0302},
            {42.24087, -83.26965},
            {42.13949, -83.17826},
            {43.00141, -85.76809},
            {42.47754, -83.0277},
            {42.7392, -84.62082},
            {42.28143, -83.38632},
            {42.3242, -83.40021},
            {42.21421, -83.14992},
            {42.91336, -85.70531},
            {42.24115, -83.61299},
            {46.91054, -98.70844},
            {40.92501, -98.34201},
            {40.58612, -98.38839},
            {40.69946, -99.08148},
            {41.37477, -83.65132},
            {41.28449, -84.35578},
            {41.35033, -83.12186},
            {40.74255, -84.10523},
            {41.64366, -83.48688},
            {41.557, -83.62716},
            {40.14477, -84.24244},
            {40.28422, -84.1555},
            {41.71894, -83.71299},
            {41.1145, -83.17797},
            {41.66394, -83.55521},
            {40.0395, -84.20328},
            {45.4647, -98.48648},
            {42.58474, -87.82119},
            {44.08861, -87.65758},
            {42.72613, -87.78285},
            {43.75083, -87.71453},
            {33.37032, -112.58378},
            {31.34455, -109.54534},
            {35.19807, -111.65127},
            {32.65783, -114.41189},
            {35.18944, -114.05301},
            {34.4839, -114.32245},
            {31.34038, -110.93425},
            {34.23087, -111.32514},
            {34.54002, -112.4685},
            {34.58941, -112.32525},
            {31.47148, -110.97648},
            {36.82523, -119.70292},
            {36.74773, -119.77237},
            {36.59634, -119.4504},
            {36.70801, -119.55597},
            {36.57078, -119.61208},
            {38.93324, -119.98435},
            {39.09193, -108.44898},
            {37.27528, -107.88007},
            {39.06387, -108.55065},
            {38.47832, -107.87617},
            {39.5186, -104.76136},
            {38.25445, -104.60914},
            {38.35, -104.72275},
            {37.7528, -100.01708},
            {37.97169, -100.87266},
            {37.04308, -100.921},
            {32.42067, -104.22884},
            {34.4048, -103.20523},
            {36.72806, -108.21869},
            {35.52808, -108.74258},
            {32.70261, -103.13604},
            {32.31232, -106.77834},
            {35.97859, -114.83249},
            {39.1638, -119.7674},
            {39.60797, -119.25183},
            {36.80553, -114.06719},
            {36.20829, -115.98391},
            {39.52963, -119.8138},
            {39.64908, -119.70741},
            {39.53491, -119.75269},
            {39.5963, -119.77602},
            {35.222, -101.8313},
            {32.2504, -101.47874},
            {31.75872, -106.48693},
            {34.81506, -102.3977},
            {31.69261, -106.20748},
            {33.57786, -101.85517},
            {31.99735, -102.07791},
            {31.84568, -102.36764},
            {35.53616, -100.95987},
            {34.18479, -101.70684},
            {31.65456, -106.30331},
            {31.63622, -106.29054},
            {31.84235, -102.49876},
            {37.67748, -113.06189},
            {37.10415, -113.58412},
            {37.13054, -113.50829},
            {58.30194, -134.41972},
            {40.41628, -120.65301},
            {43.6135, -116.20345},
            {43.66294, -116.68736},
            {47.67768, -116.78047},
            {43.69544, -116.35401},
            {43.46658, -112.03414},
            {43.49183, -116.42012},
            {46.41655, -117.01766},
            {46.38044, -116.97543},
            {43.61211, -116.39151},
            {46.73239, -117.00017},
            {43.54072, -116.56346},
            {42.8713, -112.44553},
            {47.71796, -116.95159},
            {43.82602, -111.78969},
            {42.56297, -114.46087},
            {45.67965, -111.03856},
            {46.00382, -112.53474},
            {47.50024, -111.30081},
            {46.59271, -112.03611},
            {48.19579, -114.31291},
            {46.87215, -113.994},
            {46.80833, -100.78374},
            {46.87918, -102.78962},
            {46.82666, -100.88958},
            {48.23251, -101.29627},
            {41.12389, -100.76542},
            {41.86663, -103.66717},
            {40.83242, -115.76312},
            {42.20681, -121.73722},
            {44.05817, -121.31531},
            {44.9279, -122.98371},
            {44.98595, -122.98287},
            {44.99012, -123.02621},
            {42.22487, -121.78167},
            {45.67208, -118.7886},
            {44.27262, -121.17392},
            {44.9429, -123.0351},
            {44.08054, -103.23101},
            {41.51021, -112.0155},
            {41.11078, -112.02605},
            {41.13967, -112.0505},
            {41.73549, -111.83439},
            {41.30716, -111.96022},
            {41.223, -111.97383},
            {40.0444, -111.73215},
            {41.16161, -112.02633},
            {41.19189, -111.97133},
            {40.11496, -111.65492},
            {40.16523, -111.61075},
            {41.08939, -112.06467},
            {40.53078, -112.29828},
            {47.64995, -117.23991},
            {46.73127, -117.17962},
            {47.65966, -117.42908},
            {47.67323, -117.23937},
            {46.06458, -118.34302},
            {41.58746, -109.2029},
            {20.89472, -156.47},
            {21.40222, -157.73944},
            {21.40929, -157.80092},
            {20.75548, -156.45446},
            {21.34694, -158.08583},
            {21.45, -158.00111},
            {21.39722, -157.97333},
            {21.50211, -158.02104},
            {20.89111, -156.50472},
            {21.38667, -158.00917},
            {21.34417, -158.03083},
            {19.72972, -155.09},
            {21.30694, -157.85833},
            {61.32139, -149.56778},
            {64.83778, -147.71639},
            {61.21806, -149.90028},
            {64.8, -147.53333},
            {45.90194, -112.65708},
            {21.35237, -158.08655},
            {21.4936, -158.06151},
            {39.82861, -86.38224}
        };
        const int GMToffsets[313] = {
            -6,
            -6,
            -6,
            -6,
            -6,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -6,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -6,
            -6,
            -6,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -6,
            -5,
            -6,
            -5,
            -5,
            -6,
            -5,
            -5,
            -6,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -6,
            -5,
            -5,
            -5,
            -6,
            -6,
            -6,
            -6,
            -5,
            -6,
            -6,
            -6,
            -5,
            -6,
            -5,
            -5,
            -6,
            -5,
            -5,
            -5,
            -6,
            -5,
            -5,
            -6,
            -6,
            -5,
            -5,
            -6,
            -5,
            -5,
            -5,
            -5,
            -6,
            -6,
            -5,
            -5,
            -5,
            -6,
            -6,
            -5,
            -6,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -6,
            -6,
            -6,
            -6,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -5,
            -6,
            -6,
            -6,
            -6,
            -6,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -6,
            -6,
            -6,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -6,
            -6,
            -7,
            -6,
            -7,
            -6,
            -6,
            -6,
            -6,
            -6,
            -7,
            -7,
            -6,
            -7,
            -7,
            -7,
            -9,
            -8,
            -7,
            -7,
            -8,
            -7,
            -7,
            -7,
            -8,
            -8,
            -7,
            -8,
            -7,
            -7,
            -8,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -6,
            -7,
            -6,
            -6,
            -6,
            -7,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -8,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -7,
            -8,
            -8,
            -8,
            -8,
            -8,
            -7,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -10,
            -9,
            -9,
            -9,
            -9,
            -7,
            -10,
            -10,
            -5
        };
        const bool usesDST[313] = {
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            false,
            true,
            true,
            true,
            true,
            true,
            false,
            false,
            true
        };
 
        for (int ii = 0; ii < _numCities; ii++) {
            //find the distance between my coordinates and the next city on the list
            thisDistance = GPSTimeZoneLookup::distanceBetween(latitude,longitude,_cityCoords[ii][0],_cityCoords[ii][1]);
            if (thisDistance < _closestCityDistance) {
                _closestCityDistance = thisDistance;
                _minIndex = ii;
                _closestCityLat =  _cityCoords[ii][0];
                _closestCityLong = _cityCoords[ii][1];
                _closestCityUsesDST = usesDST[ii];
                _closestCityGMTOffset = GMToffsets[ii];
            }
        }
}


double GPSTimeZoneLookup::distanceBetween(double lat1, double long1, double lat2, double long2)
{
  // this function was taken from TinyGPSPlus
  // http://arduiniana.org/libraries/tinygpsplus/
  // returns distance in meters between two positions, both specified
  // as signed decimal-degrees latitude and longitude. Uses great-circle
  // distance computation for hypothetical sphere of radius 6372795 meters.
  // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
  // Courtesy of Maarten Lamers
  double delta = radians(long1-long2);
  double sdlong = sin(delta);
  double cdlong = cos(delta);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  double slat1 = sin(lat1);
  double clat1 = cos(lat1);
  double slat2 = sin(lat2);
  double clat2 = cos(lat2);
  delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
  delta = sq(delta);
  delta += sq(clat2 * sdlong);
  delta = sqrt(delta);
  double denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
  delta = atan2(delta, denom);
  return delta * 6372795;
}
  
