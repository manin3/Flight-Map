Leading Question and Graph Algorithms 

For our project we want to accomplish three goals. 
The first goal we want to accomplish is implementing a search algorithm. Given a node, or in our case the name of an airport, we want to search the graph for that exact airport. The algorithm we will use for this is DFS (depth first search). The input that this function will take is the node we are trying to find. The output will be the value of the node that matches the passed node. Our Big O runtime for this algorithm is O(e + n) where e is the number of edges, and n is the number of nodes. 

The second goal we have for this project is to find the shortest path between any two nodes. For this goal we will use Dijkstra's algorithm to find the shortest path between two airports. The input for this function will be the two nodes that we want to find the shortest path between. The output will be a list of the nodes (airports) that make up the shortest path. For the weights, we will calculate and use the physical distance between the airports. The Big O runtime we are expecting is O(e*logn) where e is the number of edges, and n is the number of nodes. 
For our third goal we want to find out the importance of or how well connected a given node (airport) is. For this goal we will calculate the betweenness centrality using Brandes Algorithm. The input for this method is the node we are trying to find the Betweenness Centrality for. The output for this graph is a value that describes the Centrality of a given node. Our target Big O runtime is O(ne + n^2 logn), where n is the number of nodes, and e is the number of edges.

Dataset Acquisition and Processing
We will use the OpenFlights Data set. We will download the airports.dat and routes.dat files and store it on VScode and parse the data into a graph. The nodes of the graph represent airports, and we will obtain these from the airports.dat file, and the edges represent a route/flight between the two airports, which we will obtain from the routes.dat file. Our graph will be represented using adjacency lists, where we will keep a list of all the nodes that are adjacent to (have a connecting flight to) a particular node. The weights of the edges will be the distance between the two airports that are connected which can be calculated from the latitudes and longitudes listed in the airports.dat file. If there is an incomplete entry in our dataset we will disregard it. 

Timeline 

Week 1: Our goal is to acquire the data this week.

Week 2: Our goal is to complete DFS this week.

Week 3: Our goal is to implement Dijkstra's algorithm this week.

Week 4: Our goal is to start implementation of Brandes algorithm this week.

Week 5: Our goal is to finish implementation of Brandes algorithm this week.


