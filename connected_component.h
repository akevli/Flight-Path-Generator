#pragma once


#include <queue>
#include <fstream>
#include <iostream>
#include "edge.h"
#include "graph.h"

using namespace std;


class ConnectedComponents {

    private:
        vector<int> elems;
    public:
        /**
         * @param num - Number of elements to add to the disjoint set
         */ 
        void addelements(int num);

        /**
         * @param elem - Element for which to find the representative element
         * @return - Index of the representative element of the set
         */ 
        int find(int elem);

        /**
         * @param a - First element set to union
         * @param b - Second element set to union
         */ 
        void setunion(int a, int b);

        /**
         * @param map - Map with airport ids as the key and pointers to airports as the values
         */ 
        void calculateConnectedComponents(unordered_map<int, Airport*>& map);
};