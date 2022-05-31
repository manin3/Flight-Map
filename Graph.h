#pragma once

#include "airport_Map.h"
#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <list>
#include <map>

using std::string;
using std::vector;
using std::pair;
using std::list; 
using std::map;

/**
 * Class that contains the implementations of all the algorithms we take advantage of
 * (DFS, Dijkstra's Algorithm, Brandes Algorithm for Betweeness Centrality)
 */ 
class Graph {
public:
    /**
     * @param string airportdat
     * Name of Airport Data file
     * @param string routedat
     * Name of Route Data file
     */
    Graph(string airportdat, string routedat);

    /**
     * 
     */ 
    std::vector<int> search(int start_airportID, int dest_airportID);

    /**
     * @param int start_airportId
     * @param int dest_AirportID
     * Implementation of Dijkstra's algorithm to calculate and return shortest path/distance between two Airports
     */
    std::pair<vector<string>, double> Dijkstra(int start_airportId, int dest_AirportID);
    
    /**
     * @param int starting_airport ID
     * DFS traversal implementation
     */ 
    void DFS(int starting_airport);
    
    /**
     * @param int starting_airport ID of starting airport
     * Calculates betweeness centrality of a given Airport using Brandes Algorithm
     */
    float betweeness_centrality(int starting_airport);
    
    Airport_Map* everything;
    std::vector<bool> visited;
private:
    Graph graph( string &airportdat,  string &routedat);
    int starting_airport;
    std::stack<std::pair<string, string> > stack_;
    std::string airports;
    std::string routes;
};
