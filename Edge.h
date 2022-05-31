#pragma once
using namespace std;

/**
 * Class to hold data corresponding to flights between two airports.
 * Stores: ID of current airport, ID of connecting airport, Distance between the two airports
 */
class Edge{
    public:
        /**
         * @param const Edge&  reference to other Edge to compare with
         * Operator < to compare two Edges based on their distances/weights
         */ 
        bool operator<(const Edge& other) const {
            return distance < other.distance;
        }

        /**
         * @param Edge&  reference to other Edge to compare with
         * Operator == to compare two Edges based on their ID's
         */ 
        bool operator==(Edge& other) const {
            if (current_ID == other.current_ID && connection_ID == other.connection_ID)
                return true;
            return false;
        }

        /**
         * Data stored within Edge Class
         */
        int current_ID;
        int connection_ID;
        double distance = -1;
    private:
        
};