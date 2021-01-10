#pragma once

#include <queue>
#include "edge.h"
#include "graph.h"
#include "dijkstra.h"


class Landmark {
    public:
        /**
         * @param graph - Graph in which to perform Landmark path on
         * @param airports - Path of the desired airports
         * @return - A vector of vectors of the shortest path between two airports;
         */ 
        vector<vector<Vertex>> findLandmarkPath(Graph& graph, vector<Vertex> airports);
};