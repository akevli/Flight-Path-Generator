#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include "airport.h"
#include "graph.h"

using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;


class EdgeParser {
    
    private:
        ifstream file;

    public:

        /**
         * @param file_path - File path of the file to open
         * @return - True if the file was successfully opened; False otherwise
         */ 
        bool OpenFile(const string& file_path);

        /**
         * @param graph - Graph in which to create the edges
         * @param map - Map which holds the airport id as the key and a pointer to an Airport as the value
         * Linkes the vertices together in the graph
         */ 
        void CreateEdges(Graph& graph, const unordered_map<int, Airport*> map);

        /**
         * @param degree - Angle in degrees
         * @return - Value of the angle in radians as a double
         */ 
        double convertToRadians(const double degree);

        /**
         * @param lat1 - Latitude of the first point
         * @param long1 - Longitude of the first point
         * @param lat2 - Latitude of the second point
         * @param long2 - Longitud of the second point
         * @return - Distance between the two points in kilometers
         */ 
        double calculateDistance(double lat1, double long1, double lat2, double long2);

};