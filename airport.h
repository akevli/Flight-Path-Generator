#pragma once
#include <string>

using std::string;

struct Airport {
    int id;
    string name;
    string city;
    string country;
    string IATA;
    string ICAO;
    double latitude;
    double longitude;
    double altitude;
    double time_zone;
    string DST;
    string TZ_database_time;
    string type;
    string source;
    string label;
};