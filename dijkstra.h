// YEET
#pragma once

#include <queue>
#include "edge.h"
#include "graph.h"

using std::queue;
using std::priority_queue;

class Dijkstra {
    public:
        /**
         * @param graph - Graph to perfrom Dijkstra's algorithm on
         * @param s - Source Vertex
         * @param d - Destination Vertex
         * @return - Shortest path between the source and destination in the graph as a vector of vertices
         */ 
        vector<Vertex> DijkstraSSSP(Graph& graph, Vertex s, Vertex d);
    
    class Compare {
        public:
            int operator()(const pair<Vertex, int> a, const pair<Vertex, int> b) {
                return a.second > b.second;
            }
    };
};