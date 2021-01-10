#include "connected_component.h"

    void ConnectedComponents::addelements(int num) {
        for (int i = 0; i < num; i++) {
            elems.push_back(-1);
        }
    }

    int ConnectedComponents::find(int elem) {
        if (elems[elem] < 0) {
            return elem;
        }
        return find(elems[elem]);
    }

    void ConnectedComponents::setunion(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        int newSize = elems[a] + elems[b];

        if (elems[a] < elems[b]) {
            elems[b] = a;
            elems[a] = newSize;
        } else {
            elems[a] = b;
            elems[b] = newSize;
        }


    }

    void ConnectedComponents::calculateConnectedComponents(unordered_map<int, Airport*>& map) {
        elems.push_back(0);

        addelements(14110);

        ifstream file;
        string file_path = "data/routes.dat";
        file.open(file_path);

        string line;

        // Parse routes file
        while(getline(file, line)) {
            stringstream s_stream(line);
            vector<string> results;
            while(s_stream.good()) {
                string sub;
                getline(s_stream, sub, ',');
                results.push_back(sub);
            }

            if (results.at(3) == "\\N" || results.at(5) == "\\N") {
                continue;
            }
        
            if (map.find(stoi(results.at(3))) == map.end() || map.find(stoi(results.at(5))) == map.end()) {
                continue;
            }

            setunion(stoi(results.at(3)), stoi(results.at(5)));
        }

        int count = 0;
        for (int i = 1; i < (int) elems.size(); i++) {
            if (elems[i] < 0) {
                count++;
            }
        }

        count -= 6412;

        std::cout << "COUNT: " << count << std::endl;
    }