#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "../graph.h"
#include "../edge.h"
#include "../vertex_parser.h"
#include "../edge_parser.h"
#include "../BFS_Traversal.h"
#include "../dijkstra.h"
#include "../landmark_path.h"


TEST_CASE("Testing parse airports.dat into the map", "[map_vertex]") {
  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Airport*> airports = parser.GenerateVertices();
  unordered_map<int, Airport*> map;

  for (int i = 0; i < (int) airports.size(); i++) {
    if (!graph.vertexExists(airports.at(i))) {
      graph.insertVertex(airports.at(i));
      map[airports.at(i)->id] = airports.at(i);
    }
  }

  // Basic test cases
  SECTION("Correct number of vertices") {
    REQUIRE( map.size() == graph.getNumVertices() );
  }

  SECTION("Correct random vertex") {
    int rand = 153;
    REQUIRE( map.at(153) -> latitude == 48.0532989502 );
  }

  SECTION("Correct random data from Airport struct") {
    int rand = 153;
    string output = "\"A\"";
    REQUIRE( (map.at(153) -> DST) == output );
  }

  SECTION("Correct id from Airport struct") {
    REQUIRE( (map.at(1) -> id) == 1 );
  }

  SECTION("Correct name from Airport struct") {
    string output = "\"Goroka Airport\"";
    REQUIRE( (map.at(1) -> name) == output );
  }

  SECTION("Correct city from Airport struct") {
    string output = "\"Goroka\"";
    REQUIRE( (map.at(1) -> city) == output );
  }

  SECTION("Correct country from Airport struct") {
    string output = "\"Papua New Guinea\"";
    REQUIRE( (map.at(1) -> country) == output );
  }

  SECTION("Correct IATA from Airport struct") {
    string output = "\"GKA\"";
    REQUIRE( (map.at(1) -> IATA) == output );
  }

  SECTION("Correct ICAO from Airport struct") {
    string output = "\"AYGA\"";
    REQUIRE( (map.at(1) -> ICAO) == output );
  }

  SECTION("Correct latitude from Airport struct") {
    REQUIRE( (map.at(1) -> latitude) == -6.081689834590001 );
  }

  SECTION("Correct longitude from Airport struct") {
    REQUIRE( (map.at(1) -> longitude) == 145.391998291 );
  }

  SECTION("Correct altitude from Airport struct") {
    REQUIRE( (map.at(1) -> altitude) == 5282 );
  }

  SECTION("Correct time_zone from Airport struct") {
    REQUIRE( (map.at(1) -> time_zone) == 10 );
  }

  SECTION("Correct DST from Airport struct") {
    string output = "\"U\"";
    REQUIRE( (map.at(1) -> DST) == output );
  }

  SECTION("Correct TZ_database_time from Airport struct") {
    string output = "\"Pacific/Port_Moresby\"";
    REQUIRE( (map.at(1) -> TZ_database_time) == output );
  }

  SECTION("Correct type from Airport struct") {
    string output = "\"airport\"";
    REQUIRE( (map.at(1) -> type) == output );
  }

  SECTION("Correct source from Airport struct") {
    string output = "\"OurAirports\"";
    REQUIRE( (map.at(1) -> source) == output );
  }

  // Edge test cases
  SECTION("Correct last vertex") {
    int last = 14110;
    string output = "\"Melitopol Air Base\"";
    REQUIRE( (map.at(last) -> name) == output );
  }
}

TEST_CASE("Tesitng parse routes.dat into the map", "[map_edge]") {
  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Airport*> airports = parser.GenerateVertices();
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

  // Basic test cases
  SECTION("Edge exists") {
    REQUIRE( graph.edgeExists(map[3797], map[3670]) );
  }

  SECTION("Correct distance from source airport to destination airport") {
    // In kilometers
    int distance = 2234;
    REQUIRE( (int) graph.getEdgeWeight(map[3797], map[3670]) == distance );
  }

  SECTION("Invalid edge does not exist") {
    bool isExist = graph.edgeExists(map[3797], map[103020]);
    REQUIRE( !isExist );
  }

  // Edge test cases
  SECTION("Invalid source airport") {
    bool isExist = graph.edgeExists(map[-1], map[3797]);
    REQUIRE( !isExist );
  }

  SECTION("Invalid destination airport") {
    bool isExist = graph.edgeExists(map[3797], map[-2]);
    REQUIRE( !isExist );
  }

  SECTION("Invalid source and desitnation airport") {
    bool isExist = graph.edgeExists(map[-1], map[-2]);
    REQUIRE( !isExist );
  }
}

TEST_CASE("Testing BFS_Traversal", "[BFS]") {

  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Airport*> airports = parser.GenerateVertices();
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
  BFS bfs;
  SECTION("BFS writes to file") {
    string line;
    ifstream myfile ("BFStraversal.txt");
    REQUIRE(myfile.is_open());
    if (myfile.is_open())
    {
      int count = 0;
      while ( getline (myfile,line)) count++;
      myfile.close();
      REQUIRE(count == 37021);
    }
  }
}

TEST_CASE("Testing edge_parser helper functions", "[edge_parser]") {
  EdgeParser edge_parser;

  SECTION ("Test convertToRadians Function") {
      REQUIRE( edge_parser.convertToRadians(180) == M_PI);
  }

  SECTION ("Test negative degrees") {
      REQUIRE( edge_parser.convertToRadians(-180) == -M_PI);
  }

  SECTION ("Test over 360 degrees") {
      REQUIRE( edge_parser.convertToRadians(540) == 3*M_PI);
  }

  SECTION ("Test calculateDistance function") {
      double airport1_lat = -6.081689834590001;
      double airport1_long = 145.391998291;
      double airport2_lat = -5.20707988739;
      double airport2_long = 145.789001465;
      REQUIRE( (int) edge_parser.calculateDistance(airport1_lat, airport1_long, airport2_lat, airport2_long) == 106);
  }

}

TEST_CASE("Testing Dijkstra's Algorithm", "[dijkstra]") {

  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Airport*> airports = parser.GenerateVertices();
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

  Dijkstra dijkstra;
  SECTION ("Dijkstra's finds shortest path between two directly linked airports") {
    vector<Vertex> path = dijkstra.DijkstraSSSP(graph, map[3830], map[156]);
    REQUIRE(path.size() == 2);
    REQUIRE(path[0]->IATA == "\"ORD\"");
    REQUIRE(path[1]->IATA == "\"YVR\"");
  }

  SECTION ("Dijkstra's finds shortest path between two indirectly linked airports") {
    vector<Vertex> path = dijkstra.DijkstraSSSP(graph, map[3830], map[3131]);
    REQUIRE(path.size() == 3);
    REQUIRE(path[0]->IATA == "\"ORD\"");
    REQUIRE(path[1]->IATA == "\"DEL\"");
    REQUIRE(path[2]->IATA == "\"BLR\"");
  }
}

TEST_CASE("Testing Landmark Algorithm", "[landmark]") {

  Graph graph(true, true);

  VertexParser parser;
  parser.OpenFile("data/airports.dat");
  vector<Airport*> airports = parser.GenerateVertices();
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

  Landmark landmark;
  SECTION ("Landmark finds shortest path between three linked airports") {
    vector<Vertex> path;
    path.push_back(map[3830]);
    path.push_back(map[3131]);
    path.push_back(map[3361]);
    vector<vector<Vertex>> full_path = landmark.findLandmarkPath(graph, path);
    vector<int> correct_path{3830, 3093, 3131, 3131, 3304, 3361};
    int i = 0;
    for (vector<Vertex> p : full_path) {
      for (Vertex v : p) {
        REQUIRE(v->id == correct_path[i++]);
      }
    }
  }
}