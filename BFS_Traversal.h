#pragma once

#include <queue>
#include "edge.h"
#include "graph.h"

using std::queue;

class BFS {

    public:
    
        /**
         * @param graph - Graph to perfrom BFS on
         */ 
        void search(Graph& graph);

        /**
         * @param graph - Graph to perfrom BFS on
         * @param v - Vertex to explore adjacent edges on
         */ 
        void search(Graph& graph, Vertex v);

        /**
         * Save results from BFS traversal to a file
         * @param graph - Graph where edges are stored
         */ 
        void writeToFile(Graph& graph);

    private:
        vector<bool> visited;
        vector<Edge> edges;
};