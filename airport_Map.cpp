#include "airport_Map.h"


Airport_Map::Airport_Map(const string &airportdat, const string &routedat):airportdat_(airportdat) ,routedat_(routedat) {
    airport_file_to_line();
    routes_file_to_line();
}

void Airport_Map::airport_file_to_line() {
    size_ = 0;
    fstream file;
    file.open(airportdat_.c_str());

    if (file.is_open()){
        string line;
        while(getline(file, line)){
            vector<string> inputLine = line_to_airport(line);
            int ID = atoi(inputLine[0].c_str());
            double lat = atof(inputLine[6].c_str());
            double lon = atof(inputLine[7].c_str());
            // string code = inputLine[4].c_str();
            Airport vertex;
            vertex.id_ = ID;
            vertex.lat_ = lat;
            vertex.lon_ = lon;
            // vertex.code_ = code;
            if (airport_Map.count(ID) == 0) {
                airport_Map[ID] =  vertex;
                size_++;
            }  
            // if (code_Map.count(ID) == 0) {
            //     code_Map[ID] = code;
            // }     
        }
        file.close();
    }
}

vector<string> Airport_Map::line_to_airport(const string &s){
	vector<string> vec;
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==','){
			vec.push_back(temp);
			temp = "";
		}
		else{
			temp += s[i];
		}
		
	}
    vec.push_back(temp);
    return vec;
}

void Airport_Map::routes_file_to_line(){
    fstream file;
    file.open(routedat_.c_str());

    if (file.is_open()){
        string line;
        while(getline(file, line)){
            vector<string> inputLine = line_to_route(line);
            int currentID = atoi(inputLine[3].c_str());
            int connectedID = atoi(inputLine[5].c_str());
            double dist = get_distance(currentID, connectedID);
            Edge edge;
            edge.current_ID = currentID;
            edge.connection_ID = connectedID;
            edge.distance = dist;
            if (airport_Map[currentID].connections.count(connectedID) == 0) {
                airport_Map[currentID].connections[connectedID] = edge;
            }
        }
        file.close();
    }
}

vector<string> Airport_Map::line_to_route(const string &s) { 
	vector<string> vec;
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==','){
			vec.push_back(temp);
			temp = "";
		}
		else{
			temp += s[i];
		}
		
	}
    vec.push_back(temp);
    return vec;
}

double Airport_Map::get_distance(int current_airport_ID, int connected_airport_ID) {
    double lat1 = airport_Map[current_airport_ID].lat_;
    double lon1 = airport_Map[current_airport_ID].lon_;
    double lat2 = airport_Map[connected_airport_ID].lat_;
    double lon2 = airport_Map[connected_airport_ID].lon_;


    const double R = 6371e3; // const R = 6371e3; // metres
    const double pi = 3.14159265358979323846;
    double delta_phi = (lat2 - lat1) * pi / 180.0; // const Δφ = (lat2-lat1) * Math.PI/180;
    double delta_lambda = (lon2 - lon1) * pi / 180.0; // const Δλ = (lon2-lon1) * Math.PI/180;
    double phi1 = lat1 * pi / 180.0; // const φ1 = lat1 * Math.PI/180; // φ, λ in radians
    double phi2 = lat2 * pi / 180.0; // const φ2 = lat2 * Math.PI/180;
    double a = sin(delta_phi/2)*sin(delta_phi/2) + cos(phi1) * cos(phi2) * sin(delta_lambda/2)*sin(delta_lambda/2);// const a = Math.sin(Δφ/2) * Math.sin(Δφ/2) +
                                                                                    //           Math.cos(φ1) * Math.cos(φ2) *
                                                                                    //           Math.sin(Δλ/2) * Math.sin(Δλ/2);
    double c = 2 * atan2(sqrt(a), sqrt((1-a))); // const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
    return  R * c; // const d = R * c; // in metres
}

int Airport_Map::getSize(){
    return size_;
}