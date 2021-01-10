#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "airport.h"

using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;


class VertexParser {
    private:
        ifstream file;

    public:
        /**
         * @param file_path - File path of the file to open
         * @return - True if the file was successfully opened; False otherwise
         */
        bool OpenFile(const string& file_path);

        /**
         * @return - A Vector of all the vertices to be added to a graph
         */
        vector<Airport*> GenerateVertices();
};