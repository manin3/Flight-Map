#include "Graph.h"
#include "Edge.h"
#include "airport_Map.h"
#include <float.h>

// using namespace std;

/**
 * @brief Constructor for Graph objects
 * 
 * @param string refrerence for airport data
 * @param string refrence for route data
 * 
 */
Graph::Graph(string airportdat, string routedat):airports(airportdat), routes(routedat)  {
    everything = new Airport_Map(airportdat, routedat);
}


vector<int> Graph::search(int start_airportID, int dest_airportID) {
    vector<bool> visited(7649);    // hard coded the size of airport vector;
    for (int i  = 0; i < 7649; i++) {
        visited[i] = false;         // initializes all airports to be unvisited;
    }

    stack<int> airport_stack;    //  stack for traversal;
    vector<int> previous(7649);     //the vector of previously visited airports;
    previous[start_airportID] = start_airportID;
    airport_stack.push(start_airportID);   //  pushing the staring airport start_airportID;
    int current = start_airportID;    //  current airport being visited;

    while (!airport_stack.empty()) {
        current = airport_stack.top();
        airport_stack.pop();
        for (const auto & it : everything->airport_Map[current].connections) {    //  searches all airports;
            if (!visited[it.first]) {  //  the next airport in DFS traversal;
                previous[it.first] = current;
                airport_stack.push(it.first);
                visited[it.first] = true;
            }
        }
        if (current == dest_airportID) {break;} // DFS until dest_airportID is reached;
        
    }

    if (current != dest_airportID) { // checks if no path could be found using DFS;
        vector<int> null_path;
        return null_path;   // returns null_path if there was not path from start to destination;
    }

    //  trace back path from dest_airportID to start_airportID;
    queue<int> pathId;
    while (current != start_airportID) {
        pathId.push(current);
        current = previous[current];
    }
    pathId.push(start_airportID);

    vector<int> path;
    while (!pathId.empty()) {
        int ap = pathId.front();
        path.push_back(ap);
        pathId.pop();
    }
    std::reverse(path.begin(), path.end());
    return path;    // returns the path of airportID as vector<int>;
}

pair<vector<string>, double> Graph::Dijkstra(int start_airportID, int dest_airportID) {
    vector<double> distance_From_Start(everything->getSize());
    vector<int> prior_AirportID(everything->getSize());
    vector<int> unvisited;

    if (everything->airport_Map[start_airportID].connections.empty() || everything->airport_Map[dest_airportID].connections.empty()) {
        vector<string> errMessage;
        errMessage.push_back("No commercial flights exist");
        pair<vector<string>,double> M (errMessage, -1.0);
        return M;
    }

    for (const auto & it : everything->airport_Map) {
        distance_From_Start[it.first] = DBL_MAX; 
        unvisited.push_back(it.first);
    }
    distance_From_Start[start_airportID] = 0;   
    prior_AirportID[start_airportID] = start_airportID;

    int curr;    
    while (!unvisited.empty()) {
        double minDist= DBL_MAX;   
        int minIndex;   
        int i = 0;
        while (i < unvisited.size()) {
            if (distance_From_Start[unvisited[i]] < minDist) {
                minDist = distance_From_Start[unvisited[i]];
                minIndex = i;
            }
            i++;
        }
        curr = unvisited[minIndex];  
        if (curr < 1) {
            vector<string> invalidID;
            invalidID.push_back("Invalid Airport ID Error");
            pair<vector<string>, double> M (invalidID, -1.0);
            return M;
        }
        unvisited.erase(unvisited.begin() + minIndex);    
        if (curr == dest_airportID) { 
            break;
        }
        for (const auto & it : everything->airport_Map[curr].connections) { 
            if (curr < 1) {
            vector<string> invalidID;
            invalidID.push_back("Invalid Airport ID Error");
            pair<vector<string>, double> M (invalidID, -1.0);
            return M;
            }   
            double newDist = distance_From_Start[curr] + (it.second).distance; 
            if (newDist < distance_From_Start[it.first]) {   
                distance_From_Start[it.first] = newDist;
                prior_AirportID[it.first] = curr;  
            }
        }
    }

    if (curr != dest_airportID) { 
        vector<string> noPathMessage;
        noPathMessage.push_back("No path between specified start and destination");
        pair<vector<string>,double> M (noPathMessage, -1.0);
        return M;
    }

    vector<string> path_Trace;
    while (curr != start_airportID) {
        /* if (curr < 1) {
            vector<string> invalidID;
            invalidID.push_back("Invalid Airport ID Error");
            pair<vector<string>, double> M (invalidID, -1.0);
            return M;
        }  */
        path_Trace.push_back(std::to_string(curr));
        std::cout << curr << endl;
        curr = prior_AirportID[curr];
    }
    path_Trace.push_back(std::to_string(start_airportID));
    std::reverse(path_Trace.begin(), path_Trace.end());
    
    pair<vector<string>,double> shortest_Path(path_Trace, distance_From_Start[dest_airportID]);   
    return shortest_Path;
}


float Graph::betweeness_centrality(int starting_airport) {
    float centrality = 0.0;

    // map that holds all distances
    map<int, float> distances;
    distances[starting_airport] = 0;
    
    std::deque<pair<float, int> > lastPairs;
    lastPairs.push_back(pair<float, int> (distances[starting_airport] , starting_airport));

    while (!lastPairs.empty()) {
        auto v = lastPairs.front();
        lastPairs.erase(std::remove(lastPairs.begin(), lastPairs.end(), v), lastPairs.end());
        float currentDistance = v.first;
        centrality += currentDistance;

        int vID = v.second;

        
            // loop over all edges connected to v
            for (const auto & connection : everything->airport_Map[vID].connections) {
            int w = connection.first;
            float newDistance = currentDistance + connection.second.distance;

            // check if you found it for the first time or if it is shorter than the current one
            if (distances.count(w) == 0 || newDistance < distances[w]) {
                lastPairs.erase(std::remove(lastPairs.begin(), lastPairs.end(), pair<float, int>(distances[w], w)), lastPairs.end());
                lastPairs.push_back(pair<float, int>(newDistance, w));
                distances[w] = newDistance;
            }
            
        }
    }
    if (centrality == 0.0) {
        return 0.0;
    } else {
        return 1.0/centrality;
    }
}
