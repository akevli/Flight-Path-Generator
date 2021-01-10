#include "vertex_parser.h"


bool VertexParser::OpenFile(const string& file_path) {
    file.close();
    file.open(file_path);
    return file.is_open();
}

vector<Airport*> VertexParser::GenerateVertices() {
    vector<Airport*> airports;

    string line;
    while(getline(file, line)) {

        stringstream s_stream(line);
        vector<string> results;
        while(s_stream.good()) {
            string sub;
            getline(s_stream, sub, ',');
            results.push_back(sub);
        }
        
        // Pull data from line into Airport struct
        Airport* airport = new Airport();
        airport->id = stoi(results.at(0));
        airport->name = results.at(1);
        airport->city = results.at(2);
        airport->country = results.at(3);
        airport->IATA = results.at(4);
        airport->ICAO = results.at(5);

        // Check if data is empty
        if (results.at(6) == ("\\N")) {
            airport->latitude = 0.0;
        } else {
            airport->latitude = stod(results.at(6));
        }

        if (results.at(7) == ("\\N")) {
            airport->latitude = 0.0;
        } else {
            airport->longitude = stod(results.at(7));
        }

        if (results.at(8) == ("\\N")) {
            airport->latitude = 0.0;
        } else {
            airport->altitude = stod(results.at(8));
        }

        if (results.at(9) == ("\\N")) {
            airport->latitude = 0.0;
        } else {
            airport->time_zone = stod(results.at(9));
        }

        airport->DST = results.at(10);
        airport->TZ_database_time = results.at(11);
        airport->type = results.at(12);
        airport->source = results.at(13);
        airports.push_back(airport);
    }

    return airports;
}