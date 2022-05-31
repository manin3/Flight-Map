# Flight Map
## Author
Mani Nagarathnam
## Description
I set out to achieve four goals with a dataset containing flight data:
1. Read the Airport ID's, Latitudes, and Longitudes into a directed adjacency matrix where
each node represents an Airport and each edge represents a flight connecting two airports,
with edges weighted by distance.
2. Implement the DFS algorithm to find a path between a given start and end Airport ID.
3. Implement Dijkstra's algorithm to find the shortest possible path between two Airports.
4. Implements Brandes algorithm to measure betweeness centrality, or how well connected a given Airport is.
## Instructions
1. First pull the repository:
```
    git clone https://github.com/manin3/Flight-Map.git
```
2. Then open terminal with:
```    
    CTRL + Shift + `
```
3. Compile the project with:
```    
    make all
```
4. (optional) Compile the tests:
```    
    make test
```
5. Run the project with these arguments:
    - DFS [StartAirportID] [EndAirportID]
    - Dijkstra [StartAirportID] [EndAirportID]
    - Brandes [AirportID]
```    
    ./final [Algorithm name] [Argument1] [Argument2]
```
6. (optional) Run Catch Test Suite:
```
    ./test
```
### Example Provided
1. This will run Brandes (Betweeness Centrality) algorithm on AirportID: 3488
```
make all
./final Brandes 3488
```