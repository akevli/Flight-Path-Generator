#pragma once

#include <string>
#include "airport.h"

using std::string;

struct Vertex {
    Airport* airport;
    string label;
};