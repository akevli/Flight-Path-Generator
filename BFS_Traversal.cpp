#include "BFS_Traversal.h"
#include <iostream>
#include <fstream>

void BFS::search(Graph& graph) {
    visited.resize(graph.getVertices().size());

    for (Vertex v : graph.getVertices()) {
        v->label = "UNEXPLORED";
    }

    for (Edge* e : graph.getEdgesByPointer()) {
        e->setLabel("UNEXPLORED");
    }

    for (Vertex v : graph.getVertices()) {
        if (v->label == "UNEXPLORED") {
            search(graph, v);
        }
    }
}

void BFS::search(Graph& graph, Vertex v) {
    queue<Vertex> q;
    v->label = "VISITED";
    q.push(v);
    while(!q.empty()) {
        v = q.front();
        q.pop();
        for (Vertex w : graph.getAdjacent(v)) {
            if (w->label == "UNEXPLORED") {
                graph.setEdgeLabel(v, w, "DISCOVERY");
                w->label = "VISITED";
                q.push(w);
            } else if (graph.getEdgeLabel(v, w) == "UNEXPLORED") {
                graph.setEdgeLabel(v, w, "CROSS");
            }
        }
    }
}

void BFS::writeToFile(Graph& graph) {
    std::ofstream myfile;
    myfile.open ("BFStraversal.txt");
    for (auto e : graph.getEdgesByPointer()) {
        myfile << e -> source -> name << ", " << e -> dest -> name << ", " << e->getLabel() << "\n";
    }
    myfile.close();
}