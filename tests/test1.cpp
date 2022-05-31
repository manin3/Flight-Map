#include "../airport_Map.h"
#include "../catch/catch.hpp"
#include <cmath>
#include "../Graph.h"

/**
 * Catch Testing Suite
 */ 


Airport_Map airportMap("airports.txt", "new_routes.dat.txt");
Graph graph1("tests/test_airports_1.txt", "tests/test_routes_1.txt");
Graph graph2("tests/test_airports_2.txt", "tests/test_routes_2.txt");


TEST_CASE("Check that Vertecies are being added to adjacency list"){
    REQUIRE(airportMap.airport_Map[1].id_ == 1);
    REQUIRE(airportMap.airport_Map[2].id_ == 2);
    REQUIRE(airportMap.airport_Map[6394].id_ == 6394);
    REQUIRE(airportMap.airport_Map[8195].id_ == 8195);
    REQUIRE(airportMap.airport_Map[13466].id_ == 13466);
}

TEST_CASE("Test Correct Latitude and Longitude for Airports.txt"){
    double lat1 = airportMap.airport_Map[1].lat_;
    double lon1 = airportMap.airport_Map[1].lon_;
    REQUIRE(lat1 == -6.081689834590001);
    REQUIRE(lon1 == 145.391998291);

    double lat2 = airportMap.airport_Map[2].lat_;
    double lon2 = airportMap.airport_Map[2].lon_;
    REQUIRE(lat2 == -5.20707988739);
    REQUIRE(lon2 == 145.789001465);

    double lat2713 = airportMap.airport_Map[2713].lat_;
    double lon2713 = airportMap.airport_Map[2713].lon_;
    REQUIRE(lat2713 == 7.92757);
    REQUIRE(lon2713 == -72.5115);

    double lat7429 = airportMap.airport_Map[7429].lat_;
    double lon7429 = airportMap.airport_Map[7429].lon_;
    REQUIRE(lat7429 == 4.3790202140808105);
    REQUIRE(lon7429 == -7.6969499588012695);

    double lat11288 = airportMap.airport_Map[11288].lat_;
    double lon11288 = airportMap.airport_Map[11288].lon_;
    REQUIRE(lat11288 == -5.80091);
    REQUIRE(lon11288 == 110.47838);

    double lat13607 = airportMap.airport_Map[13607].lat_;
    double lon13607 = airportMap.airport_Map[13607].lon_;
    REQUIRE(lat13607 == 36.18239974975586);
    REQUIRE(lon13607 == -86.88670349121094);
}

TEST_CASE("Check that Edges From new_routes.dat.txt are present in List"){
    /**CTRL+F in new_routes.dat.txt. However, our graph is directed 
     * and our graph deletes duplicates (whenever there is another flight between the same two airports)
     * Therefore, Num connections is usually less than half of results from CTRL+F for very popular airports
     */
    int num_connections = airportMap.airport_Map[2965].connections.size();
    REQUIRE (num_connections == 1);

    int num_connections1 = airportMap.airport_Map[7185].connections.size();
    REQUIRE (num_connections1 == 2);

    int num_connections2 = airportMap.airport_Map[3615].connections.size();
    REQUIRE (num_connections2 == 12);
    
    int num_connections3 = airportMap.airport_Map[3043].connections.size();
    REQUIRE (num_connections3 == 14);

    int num_connections4 = airportMap.airport_Map[1638].connections.size();
    REQUIRE (num_connections4 == 49); //verified using python (over 100 appearances)

    int num_connections5 = airportMap.airport_Map[13511].connections.size();
    REQUIRE (num_connections5 == 0); //shouldn't have any connections

    int num_connections6 = airportMap.airport_Map[13714].connections.size();
    REQUIRE (num_connections6 == 0); //shouldn't have any connections
}

TEST_CASE("Check that Graph is Directed"){
    /**
     * Node 41 is connected to 147 but not the other way around
     * 
     */
    bool found = false;
    bool found1 = false;
    if (airportMap.airport_Map[41].connections.find(147) != airportMap.airport_Map[41].connections.end()){
        found = true;
    }
    if (airportMap.airport_Map[147].connections.find(41) != airportMap.airport_Map[147].connections.end()){
        found1 = true;
    }   
    REQUIRE (found == true);
    REQUIRE (found1 == false);

    /**
     * Node 7238 is connected to 7239 but not the other way around
     * 
     */
    bool found2 = false;
    bool found3 = false;
    if (airportMap.airport_Map[7238].connections.find(7239) != airportMap.airport_Map[7238].connections.end()){
        found2 = true;
    }
    if (airportMap.airport_Map[7239].connections.find(7238) != airportMap.airport_Map[7239].connections.end()){
        found3 = true;
    }   
    REQUIRE (found2 == true);
    REQUIRE (found3 == false);
}

TEST_CASE("Distances Computed Correctly"){
    double distance = airportMap.airport_Map[3599].connections[8199].distance;
    double correct_dist = 159.87 * 1000; 
    //computed correct distance from: https://www.meridianoutpost.com/resources/etools/calculators/calculator-latitude-longitude-distance.php?
    //where lat1 = 60.77980042, lon1 = -161.8379974, lat2 = 60.471000671387, lon2 = -164.70100402832
    REQUIRE (correct_dist == Approx(distance).epsilon(0.005)); //check within .005% of error 

    double distance1 = airportMap.airport_Map[253].connections[302].distance;
    double correct_dist1 = 5134.6 * 1000; 
    //computed correct distance from: https://www.meridianoutpost.com/resources/etools/calculators/calculator-latitude-longitude-distance.php?
    //where lat1 = 5.261390209197998, lon1 = -3.9262900352478027, lat2 = 50.901401519800004, lon2 = 4.48443984985
    REQUIRE (correct_dist1 == Approx(distance1).epsilon(0.005)); //check within .005% of error 

    double distance2 = airportMap.airport_Map[3488].connections[3751].distance;
    double correct_dist2 = 1716.27 * 1000; 
    //computed correct distance from: https://www.meridianoutpost.com/resources/etools/calculators/calculator-latitude-longitude-distance.php?
    //where lat1 = 5.261390209197998, lon1 = -3.9262900352478027, lat2 = 50.901401519800004, lon2 = 4.48443984985
    REQUIRE (correct_dist2 == Approx(distance2).epsilon(0.005)); //check within .005% of error 
}

TEST_CASE("Checks if search runs DFS correctly"){
    cout << "testing search() function" << endl;
    vector<int> to_test = graph1.search(3, 4);
    for(unsigned i = 0; i < to_test.size(); i++){
        cout << to_test[i];
    }
    REQUIRE(to_test[to_test.size() -1] == 4);
}

TEST_CASE("Checks if search runs DFS starts correctly"){
    vector<int> to_test = graph1.search(3, 4);
    for(unsigned i = 0; i < to_test.size(); i++){
        cout << to_test[i];
    }
    REQUIRE(to_test[0] == 3);
}

// TEST_CASE("Check that NULL paths have a length of 0"){
//     graph = new Graph(airports(airportdat), routes(routedat);
//     REQUIRE(graph.search(7094, 951).size() == 0);
//     REQUIRE(graph.search(580, 1278).size() == 0);
//     REQUIRE(graph.search(1276, 1418).size() == 0);
//     REQUIRE(graph.search(1415, 1324).size() == 0);
// }

TEST_CASE("Test Dijkstra no connections gives correct error for starting airport") {
    vector<string> message = graph1.Dijkstra(6, 1).first;
    double dist = graph1.Dijkstra(6,1).second;
    REQUIRE (message[0].compare("No commercial flights exist") == 0);
    REQUIRE (dist == -1.0);
}

TEST_CASE("Test Dijkstra no connections gives correct error for destination airport") {
    vector<string> message = graph1.Dijkstra(3, 6).first;
    double dist = graph1.Dijkstra(3,6).second;
    REQUIRE (message[0].compare("No commercial flights exist") == 0);
    REQUIRE (dist == -1.0);
}

// TEST_CASE("Test Dijkstra Direct Flights") {
//     vector<string> path1 = graph1.Dijkstra(3, 2).first;
//     double dist1 = graph1.Dijkstra(3, 2).second;
//     REQUIRE (path1[0].compare("3 2") == 0);
//     REQUIRE (dist1 == 0);
// }


TEST_CASE("Test Betweeness Centrality: Simple"){
    double centrality2 = graph1.betweeness_centrality(2);
    double centrality1 = graph1.betweeness_centrality(1);
    double centrality4 = graph1.betweeness_centrality(4);
    REQUIRE (centrality2 > centrality4);
    REQUIRE (centrality2 > centrality1);
    REQUIRE (centrality4 > centrality1);
}

 TEST_CASE("Test Betweeness Centrality: Simple: Check that not connected gives 0 value"){
    
    double centrality1 = graph1.betweeness_centrality(1);
    double centrality5 = graph1.betweeness_centrality(5);
    REQUIRE (centrality1 == 0);
    REQUIRE (centrality5 == 0);
}

TEST_CASE("Test Betweeness Centrality: Harder"){
    double centrality6 = graph2.betweeness_centrality(6);
    double centrality5 = graph2.betweeness_centrality(5);
    double centrality2 = graph2.betweeness_centrality(2);
    double centrality1 = graph2.betweeness_centrality(1);
    REQUIRE (centrality1 > centrality2);
    REQUIRE (centrality5 > centrality2);
    REQUIRE (centrality1 > centrality5);
    REQUIRE (centrality1 > centrality6);
}

 TEST_CASE("Test Betweeness Centrality: Harder: Check that connected gives non 0 value"){
    
    double centrality1 = graph2.betweeness_centrality(1);
    double centrality13 = graph2.betweeness_centrality(7);
    REQUIRE (centrality1 != 0);
    REQUIRE (centrality13 != 0);
}
