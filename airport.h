#pragma once
#include <map>
#include <vector>
#include <cctype>
#include <algorithm>
#include "Edge.h"

/**
 * Class that stores all the data we use for Airports
 */ 
class Airport {
    public: 
        /**
         * @param Airport& other
         * == operator to compare two airports based on their ID's
         */ 
        bool operator==(Airport& other) const {
            if (id_ == other.id_) {return true;}
            return false;
        }

        /**
         * Maps all connected Airport ID's to their respective Edge Objects
         */
        map<int, Edge> connections;

        /**
         * ID, Latitude, and Longitude of current Airport
         */ 
        int id_; 
        double lat_;
        double lon_; 
        string code_;
};