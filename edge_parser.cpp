#include "edge_parser.h"

bool EdgeParser::OpenFile(const string& file_path) {
    file.close();
    file.open(file_path);
    return file.is_open();
}

void EdgeParser::CreateEdges(Graph& graph, const unordered_map<int, Airport*> map) {
    string line;

    // Parse routes file
    while(getline(file, line)) {
        stringstream s_stream(line);
        vector<string> results;
        while(s_stream.good()) {
            string sub;
            getline(s_stream, sub, ',');
            results.push_back(sub);
        }

        // Check for empty data
        if (results.at(3) == "\\N" || results.at(5) == "\\N") {
            continue;
        }
        
        if (map.find(stoi(results.at(3))) == map.end() || map.find(stoi(results.at(5))) == map.end()) {
            continue;
        }

        Airport* firstAirport = map.at(stoi(results.at(3)));
        Airport* secondAirport = map.at(stoi(results.at(5)));

        if (!graph.edgeExists(firstAirport, secondAirport)) {
            graph.insertEdge(firstAirport, secondAirport);
            graph.setEdgeWeight(firstAirport, secondAirport, calculateDistance(firstAirport->latitude, firstAirport->longitude, secondAirport->latitude, secondAirport->longitude));
        }
    }
}

double EdgeParser::calculateDistance(double lat1, double long1, double lat2, double long2) {
    double rLat1 = convertToRadians(lat1);
    double rLong1 = convertToRadians(long1);
    double rLat2 = convertToRadians(lat2);
    double rLong2 = convertToRadians(long2);

    double longDiff = rLong2 - rLong1;
    double latDiff = rLat2 - rLat1;

    // Distance Formula taking into account curvature of Earth
    double dist = pow(sin(latDiff / 2), 2) + cos(rLat1) * cos(rLat2) * pow(sin(longDiff / 2), 2);

    dist = 2 * asin(sqrt(dist));

    double earthRadius = 6371;

    return earthRadius * dist;
}

double EdgeParser::convertToRadians(const double degree) {
    return (M_PI / 180) * degree;
}