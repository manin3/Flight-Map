#pragma once
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "Edge.h"
#include "airport.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

/**
 * Class to populate the adjacency list we are using to represent this dataset.
 */ 
class Airport_Map{
    public:
        /**
         * Constructor for Aiport_Map
         * @param const string& airportdat
         * @param const string& routedat
         */ 
        Airport_Map(const string &airportdat, const string &routedat);

        /**
         * Getter for size of airport_Map
         */ 
        int getSize();

        /**
         * Adjacency list mapping each Airport ID to Airport object containing map of Edges
         */ 
        map<int, Airport> airport_Map;

        // map<int, string> code_Map;
    private:
        /**
         * @param int source airport ID
         * @param int destination airportID
         */ 
        double get_distance(int source, int dest);

        /**
         * Seperates each line in airport data file
         */ 
        void airport_file_to_line();

        /**
         * Seperates each line in route data file
         */ 
        void routes_file_to_line();

        /**
         * @param const string& line
         * Helper function to take line of data and convert to Airport Object
         */ 
        vector<string> line_to_airport(const string &line);

        /**
         * @param const string& line
         * Helper function to take line of data and convert to Airport Object
         */ 
        vector<string> line_to_route(const string &line);

        /**
         * Names of data files and size of map
         */ 
        string airportdat_;
        string routedat_;
        int size_;
};