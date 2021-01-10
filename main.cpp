#include <vector>
#include <iostream>
#include <unordered_map>

#include "graph.h"
#include "edge.h"
#include "vertex_parser.h"
#include "edge_parser.h"
#include "BFS_Traversal.h"
#include "dijkstra.h"
#include "landmark_path.h"
#include "connected_component.h"

// Gets origin airport id from user
int getOriginId(unordered_map<int, Airport*> map) {
  std::cout << "Please enter your origin airport id" << std::endl;

  int origin = 0;
  std::cin >> origin;

  while (std::cin.fail() || !map.count(origin)) {
    std::cout << "Please enter a valid origin id" << std::endl;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> origin;
  }
  std::cout << "Origin Airport: " << map[origin]->name << std::endl;
  return origin;
}

// Gets the number of destinations from user
int getNumDestinations() {
  std::cout << "How many destination airports would you like?" << std::endl;

  int num_dest = 0;
  std::cin >> num_dest;

  while (std::cin.fail() || num_dest <= 0) {
    std::cout << "Please enter a valid number of destinations" << std::endl;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> num_dest;
  }

  return num_dest;
}

// Gets destination airport id from user
int getDestinationID(unordered_map<int, Airport*> map, int num) {
  std::cout << "Please enter your destination airport id" << std::endl;

    int dest = 0;
    std::cin >> dest;

    while (std::cin.fail() || !map.count(dest)) {
      std::cout << "Please enter a valid destination id" << std::endl;
      std::cin.clear();
      std::cin.ignore(256, '\n');
      std::cin >> dest;
    }

    std::cout << "Destination #" << num + 1 << " : " << map[dest]->name << std::endl;

    return dest;
}

// Prints out the whole path
void printFullPath(vector<vector<Vertex>>& airport_path, vector<Vertex>& airport_list) {
  std::cout << "Full Path of Trip:" << std::endl;
  int count = 0;
  for (vector<Vertex> p : airport_path) {

    // Handles case where route does not exist
    if (p.size() == 0) {
      std::cout << "The route from " << airport_list.at(count) -> name << " to " << airport_list.at(count + 1) -> name << " does not exist.";
    }

    for (unsigned int i = 0; i < p.size(); i++) {
      if (i + 1 == p.size()) {
        std::cout << p[i]->name;
      } else {
        std::cout << p[i]->name << " -> ";
      }
    }
    std::cout << std::endl;
    count++;
  }
}

// Prints the total distance of the route
void printTotalDistance(int& total_distance, EdgeParser& edge_parser, vector<vector<Vertex>>& airport_path) {
  for (vector<Vertex> p : airport_path) {
    for (int i = 0; i < (int) p.size() - 1; i++) {
      total_distance += edge_parser.calculateDistance(p[i]->latitude, p[i]->longitude, p[i+1]->latitude, p[i + 1]->longitude);
    }
  }
  std::cout << "Total Distance: " << total_distance << std::endl;
}

// main program method
void userProgram() {
  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Vertex> airports = parser.GenerateVertices();
  unordered_map<int, Airport*> map;

  for (int i = 0; i < (int) airports.size(); i++) {
    if (!graph.vertexExists(airports.at(i))) {
      graph.insertVertex(airports.at(i));
      map[airports.at(i)->id] = airports.at(i);
    }
  }

  EdgeParser edge_parser;
  edge_parser.OpenFile("data/routes.dat");
  edge_parser.CreateEdges(graph, map);

  vector<Vertex> airport_list;

  int origin = getOriginId(map);
  airport_list.push_back(map[origin]);

  int num_dest = getNumDestinations();
  for (int i = 0; i < num_dest; i++) {
    int dest = getDestinationID(map, i);
    airport_list.push_back(map[dest]);
  }

  Landmark landmark;
  vector<vector<Vertex>> airport_path = landmark.findLandmarkPath(graph, airport_list);
  int total_distance = 0;
  
  printFullPath(airport_path, airport_list);
  printTotalDistance(total_distance, edge_parser, airport_path);

  std::cout << "Bon Voyage! :)" << std::endl;

  // Delete heap memory to ensure no memory leaks
  for (int i = 0; i < (int) airports.size(); i++) {
    delete airports[i];
    airports[i] = NULL;
  }
  
}

void numberOfConnectedComponents() {
  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Vertex> airports = parser.GenerateVertices();
  unordered_map<int, Airport*> map;

  for (int i = 0; i < (int) airports.size(); i++) {
    if (!graph.vertexExists(airports.at(i))) {
      graph.insertVertex(airports.at(i));
      map[airports.at(i)->id] = airports.at(i);
    }
  }
  std::cout << map[3830]->name << std::endl;
  ConnectedComponents comp;
  comp.calculateConnectedComponents(map);
}

void BFSTraversalCheck() {
  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Vertex> airports = parser.GenerateVertices();
  unordered_map<int, Airport*> map;

  for (int i = 0; i < (int) airports.size(); i++) {
    if (!graph.vertexExists(airports.at(i))) {
      graph.insertVertex(airports.at(i));
      map[airports.at(i)->id] = airports.at(i);
    }
  }

  EdgeParser edge_parser;
  edge_parser.OpenFile("data/routes.dat");
  edge_parser.CreateEdges(graph, map);

  vector<Vertex> airport_list;

  BFS bfs;
  bfs.search(graph);
  bfs.writeToFile(graph);
}

int main() {
  //BFSTraversalCheck();
  //numberOfConnectedComponents();
  userProgram();
  return 0;

}
