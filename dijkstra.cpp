#include "dijkstra.h"
#include <map>
#include <iostream>

vector<Vertex> Dijkstra::DijkstraSSSP(Graph& graph, Vertex s, Vertex d) {

    // Initialize variables
    unordered_map<Vertex, double> distances;
    unordered_map<Vertex, Vertex> previous;
    priority_queue<pair<Vertex, double>, vector<pair<Vertex, double>>, Compare> pq;
    unordered_map<Vertex, bool> visited;

    for (Vertex v : graph.getVertices()) {
        distances[v] = 20090;
        previous[v] = NULL;
        visited[v] = false;
    }

    distances[s] = 0;
    pq.push(make_pair(s, 0));

    // Perform Dijkstra's Algorithm
    pair<Vertex, double> curr = pq.top();
    while (!pq.empty() && curr.first != d) {
        curr = pq.top();
        curr.second = distances[curr.first];

        for (Vertex adj : graph.getAdjacent(curr.first)) {
            if (visited[adj]) {
                continue;
            }

            Edge edge = graph.getEdge(curr.first, adj);
            double newDistance = edge.getWeight() + distances[curr.first];
            
            if (newDistance < distances[adj]) {
                pq.push(make_pair(adj, newDistance));
                distances[adj] = newDistance;
                previous[adj] = curr.first;
            }
        }
        pq.pop();
        visited[curr.first] = true;
    }

    Vertex current = d;
    vector<Vertex> path;
    path.insert(path.begin(), d);
    bool pathExists = true;

    while (current != NULL && current != s) {
        path.insert(path.begin(), previous[current]);
        current = previous[current];

        if (current == NULL) {
            pathExists = false;
        }
    }

    if (!pathExists) {
        path.clear();
    }

    return path;
}