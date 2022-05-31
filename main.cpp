
#include "Graph.h"
#include "airport_Map.h"

#include <vector>
#include <iostream>


int main(int argc, const char * argv[]){
    Graph graph("tests/test_airports_2.txt", "tests/test_routes_2.txt");
    Graph graph1("airports.txt", "new_routes.dat.txt");
    
    if(argc == 4 && argv[1] == std::string("DFS")){
        std::cout << "DFS " << "path: " << std::endl;
        long arg2 = strtol(argv[2], NULL, 10);
        long arg3 = strtol(argv[3], NULL, 10);
        auto vec = graph.search((int)arg2, (int)arg3);
        for (const auto& number : vec){
            std::cout << number << std::endl; 
        }
    }
    if(argc == 4 && argv[1] == std::string("Dijkstra")){
        std::cout << "Dijkstra " << "path: " << std::endl;
        int arg2 = strtol(argv[2], NULL, 10);
        int arg3 = strtol(argv[3], NULL, 10);
        pair<vector<string>, double> result = graph1.Dijkstra(arg2, arg3);
        for (int i = 0; i < result.first.size(); i++) {
            std::cout << result.first[i] <<std::endl;
        }
        std::cout << result.second <<std::endl;
    }
    if(argc == 3 && argv[1] == std::string("Brandes")){
        std::cout << "Betweeness Centrality Value: " << std::endl;
        long arg2 = strtol(argv[2], NULL, 10);
        float centrality = graph.betweeness_centrality((int)arg2);
        std::cout << centrality << std::endl;
    } 
}