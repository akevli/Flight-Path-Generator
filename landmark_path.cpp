#include "landmark_path.h"

vector<vector<Vertex>> Landmark::findLandmarkPath(Graph& graph, vector<Vertex> airports) {
    Dijkstra dijkstra;
    vector<vector<Vertex>> path;

    // Perform Djiskstra's for multiple iterations
    for (unsigned int i = 0; i < airports.size() - 1; i++) {
        vector<Vertex> segment = dijkstra.DijkstraSSSP(graph, airports[i], airports[i + 1]);
        path.push_back(segment);
    }
    return path;
}