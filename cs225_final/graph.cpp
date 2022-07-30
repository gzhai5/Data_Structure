#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
#include "readFromFile.hpp"
#include "graph.h"
#include "airport.h"
#include "airline.h"
#include "cs225/PNG.h"
#include "dsets.h"

using namespace std;


// const airport graph::InvalidNode = "invalid";
// const int graph::InvalidWeight = INT_MIN;
// const string graph:: InvalidLabel = "invalid";
// const airline graph::InvalidEdge = Edge(graph::InvalidNode, graph::InvalidVertex, graph::InvalidWeight, graph::InvalidLabel);

graph::graph(){

}

/* to read from a .dat file
 *
 */ 
graph::graph(const string & file_airport, const string & file_airline){
    std::pair<std::vector<airport*>,std::vector<airline*>> nePair = file_to_airline(file_airport, file_airline);
    nodes = nePair.first;
    edges = nePair.second;      //pair nodes(airport) and edges(airline)
    size_t n = nodes.size();

    matrix.clear();
    std::vector<airline*> row;       //create a vetor list for saving all edges(airlines) while all are NULL
    for (size_t i = 0; i < n; i++) {
	row.push_back(NULL);
    }
    for (size_t i = 0; i < n; i++) {
	matrix.push_back(row);
    }
    for (airline* ptr : edges) {
	matrix[ptr->source_->id_][ptr->destination_->id_] = ptr;
    }
}

void graph::addAirport(airport* v){
    nodes.push_back(v);
    size_t n = matrix.size();
    v -> id_ = n;
    // construct a new row and append a NULL after each row
    std::vector<airline*> last = {NULL};
    for (size_t i = 0; i < n; i++) {
        matrix[i].push_back(NULL);
        last.push_back(NULL);
    }
    matrix.push_back(last);
}

/* a way to visualize the adjacency matrix
 * just written for testing
 */
void graph::print() {
    size_t n = matrix.size();
    if (n==0) { 
	return;
    }
    size_t b = 0;
    for (size_t i = 0; i < n; i++) {
	for (size_t j = 0; j < n; j++) {
	    if (matrix[i][j]) {
		b += 1;
	    }
	}
    }
    std::cout << "There are " << n << " airports and " << b << " flights in the world" << std::endl;
}

graph::~graph() {
    clear();
}

void graph::clear() {
    for (airport* p: nodes) {
        if (p){
	    delete p;
	}
    }
    /*
    for (airline* p: edges) {
	if (p) {
	    delete p;
        }
    }
    size_t n = matrix.size();
    for (size_t i = 0; i < n; i++) {
	for (size_t j = 0; j < n; j++) {
	    if (matrix[i][j]) {
	    	delete matrix[i][j];
	    }
	}
    }
    */
}

void graph::addAirline(airline * other) {
    int x = -1;
    int y = -1;
    for (size_t i = 0; i < nodes.size(); i++) {
	if (nodes[i] == other->source_) {
	    x = i;
	}
	if (nodes[i] == other->destination_) {
	    y = i;
	}
    }
    if ((x<0) || (y<0)) {
	    return;
    }
    edges.push_back(other);
    matrix[x][y] = other;
}




std::vector<airline*> graph::incidentAirline(airport* v ) {
    std::vector<airline*> resultedairline;
    unsigned idStore = v->id_;
    int incoming =0;
    int outcoming =0;
    for (size_t i = 0; i<nodes.size(); i++){
        if(matrix[i][idStore]!=NULL){
            resultedairline.push_back(matrix[i][idStore]);
            outcoming++;
        }
        if(matrix[idStore][i]!=NULL) {
            resultedairline.push_back(matrix[idStore][i]);
            incoming++;
        }
    }
    // std::cout << "For the aiport "<<v->name_<< ", there are " << incoming << " flights coming in and " << outcoming << " flights going out." << std::endl;
    return resultedairline;
    
}



bool graph::areAdjacent(airline* v1, airline* v2) {
    if (v1->source_ ==v2->source_ ||v1->source_ ==v2->destination_ ||v1->destination_ == v2->source_ ||v1->destination_ == v2->destination_){
        return true;
    }
    return false;
}





std::vector<airport*> graph::getneighborslist_of_node(airport* v){
    std::vector<airport*> all_neighbor_list;
    
    // unsigned idStore = v -> id_;
    // for (size_t i = 0; i < nodes.size(); i++){
    //     if (matrix[idStore][i] != NULL){
    //         all_neighbor_list.push_back(matrix[i][idStore] -> destination_);
    //     }
    // }


    for (size_t i = 0; i < incidentAirline(v).size(); i++){
        if (v == incidentAirline(v)[i] -> source_){
            all_neighbor_list.push_back(incidentAirline(v)[i] -> destination_);    
        }
        else{
            all_neighbor_list.push_back(incidentAirline(v)[i] -> source_);
        }
    }




    return all_neighbor_list;
}





void graph::BFS(airport* v){
    bool *visited = new bool[nodes.size()];       //intialize a list to save the status wherther one node is visited, and at first, all not visited
    for (size_t i = 0; i < nodes.size(); i++){
        visited[i] = false;
    }

    queue<airport*> airport_queue;                //initilize a airport_queue to treat the node and update v of our traversal
    airport_queue.push(v);

    std::vector<std::string> trav_path;                //create a list to save traversal path
    trav_path.push_back(v -> name_);

    // std::list<airport*>::iterator it;
    while(!airport_queue.empty()){
        v = airport_queue.front();
        airport_queue.pop();
        for (airport* w: getneighborslist_of_node(v)){
            if(!visited[w -> id_]){                                   //need debug, use visieted[id_] to do
                visited[w -> id_] = true;
                airport_queue.push(w);
                trav_path.push_back(w -> name_);
            }
        }
    }
}



std::vector<std::string> graph::BFS_path(airport* v){
    bool *visited = new bool[nodes.size()];       //intialize a list to save the status wherther one node is visited, and at first, all not visited
    for (size_t i = 0; i < nodes.size(); i++){
        visited[i] = false;
    }

    queue<airport*> airport_queue;                //initilize a airport_queue to treat the node and update v of our traversal
    airport_queue.push(v);

    std::vector<std::string> trav_path;                //create a list to save traversal path
    trav_path.push_back(v -> name_);

    // std::list<airport*>::iterator it;
    while(!airport_queue.empty()){
        v = airport_queue.front();
        airport_queue.pop();
        for (airport* w: getneighborslist_of_node(v)){
            if(!visited[w -> id_]){                                   //need debug, use visieted[id_] to do
                visited[w -> id_] = true;
                airport_queue.push(w);
                trav_path.push_back(w -> name_);
            }
        }
    }
    return trav_path;
}



double graph::calculateDistance(double latitude1,double longitude1,double latitude2,double longitude2) {
    if((latitude1==latitude2) && (longitude1==longitude2)) {
        return 0;
    }
    double distance; //convert all lon and lat from degree to radius
    double lat1=latitude1*((M_PI)/180);//deg2rad
    double lat2=latitude2*((M_PI)/180);
    double lon1=longitude1*((M_PI)/180);
    double lon2=longitude2*((M_PI)/180);

    double radius=6378; //radius of earth

    //Haversine Formula
    double dLat=lat2-lat1;  
    double dLon=lon2-lon1;
    distance=pow(sin(dLat/2),2)+cos(lat1) *cos(lat2)* pow(sin(dLon/2),2);
    distance=2* asin(sqrt(distance));
    distance*=radius;
    
    return distance;
}


double graph::calculateDistance(airport* source, airport* destination){
    double latitude1 = source -> latitude_;
    double latitude2 = destination -> latitude_;
    double longitude1 = source -> longitude_;
    double longitude2 = destination -> longitude_;
    
    return calculateDistance(latitude1, longitude1, latitude2, longitude2);
}



std::vector<airport*> graph::shortestPath(airport *source, airport *destination){    
    std::map<airport*, int> distance;
    std::map<airport*, airport*> previous;
    auto cmp = [] (std::pair<airport*, int> a, std::pair<airport*, int> b){
        return a.second >= b.second;
    };

    std::priority_queue<std::pair<airport*, int>, std::vector<std::pair<airport*, int>>, decltype(cmp) > priority_queue(cmp);
    std::vector<airport*> visited;


    airport* curr = source;
    distance[source] = 0;


    while (curr != destination){
        for (airport* neighbor: getneighborslist_of_node(curr)){
            if ((visited.empty()) || (std::find(&(visited.front()), &(visited.back()), neighbor) == &(visited.back()))){
                int dist_should_add = calculateDistance(curr, neighbor) + distance.find(curr)->second;

                if (distance.find(neighbor) != distance.end()){
                    int old_distance = distance[neighbor];
                    if (dist_should_add < old_distance){
                        distance[neighbor] = dist_should_add;
                        previous[neighbor] = curr;
                        priority_queue.push(*distance.find(neighbor));
                    }
                }
                else{
                    distance[neighbor] = dist_should_add;
                    previous[neighbor] = curr;
                    priority_queue.push(*distance.find(neighbor));
                }    
            }
        }

        visited.push_back(curr);
        if (priority_queue.size() == 0) {
            break;
        }
        curr = priority_queue.top().first;
        priority_queue.pop();
    }

    std::vector<airport*> path;
    if (curr != destination){    //if cannot find path
        return path;
    }

    path.push_back(destination);
    for (airport* i = previous[destination]; i != source; i = previous[i]) {
        path.push_back(i);
    }
    path.push_back(source);

    std::reverse(path.begin(), path.end());
    return path;
}




double graph::find_shortest(vector<double> distances){
    double shortest = distances.back();
    for (size_t i = 0; i < distances.size(); i++){
        distances.pop_back();
        if (shortest >= distances.back()){
            shortest = distances.back();
        }
    }
    return shortest;
}




//Kruskal's minimum spanning tree
struct {
    bool operator() (airline *a,airline* b) const {
        return ((a->distance)<(b->distance));
    }
} customLess;

double graph::KruskalMST(graph & g) {
    vector <airline*> edgelist =g.edges;
    vector <airline*>::iterator it;
    double min_cost=0;
    //first sort all the edges by weight
    sort(edgelist.begin(),edgelist.end(),customLess);
    //then make all the vertices into disjoint sets
    DisjointSets v;
    vector<airport*> nodelist=g.nodes;
    v.addelements(nodelist.size());
    //traverse the entire list
    for(unsigned i=0;i<edgelist.size();i++) {

        unsigned int a=edgelist[i]->source_->id_;
        unsigned int b= edgelist[i]->destination_->id_;
        //check if they are from different sets
      if(v.find(a)!=v.find(b)) {
            //if yes, we need to union them
            v.setunion(a,b);
            min_cost+=edgelist[i]->distance;
            std::cout<< min_cost <<" " <<std::endl;
        }
    }
    return min_cost;
}

vector<airline*> graph::MST() {
    vector <airline*> edgelist =this->edges;
    vector <airline*> mst_airlines;
    vector <airline*>::iterator it;
    double min_cost=0;
    //first sort all the edges by weight
    sort(edgelist.begin(),edgelist.end(),customLess);
    //then make all the vertices into disjoint sets
    DisjointSets v;
    vector<airport*> nodelist=this->nodes;
    v.addelements(nodelist.size());
    //traverse the entire list
    for(unsigned i=0;i<edgelist.size();i++) {

        unsigned int a=edgelist[i]->source_->id_;
        unsigned int b= edgelist[i]->destination_->id_;
        //check if they are from different sets
      if(v.find(a)!=v.find(b)) {
            //if yes, we need to union them
            v.setunion(a,b);
            min_cost+=edgelist[i]->distance;
            mst_airlines.push_back(edgelist[i]);
            // std::cout<< min_cost <<" " <<std::endl;
        }
    }
    return mst_airlines;
}

    cs225::PNG graph::plotNodes() {
	size_t n = nodes.size();
	cs225::PNG world(2000,1000);
	for (unsigned i = 0; i < 2000; i++) {
	    world.getPixel(i,500) = cs225::HSLAPixel(0,0,0);
	}
	for (unsigned i = 0; i < 1000; i++) {
	    world.getPixel(1000,i) = cs225::HSLAPixel(0,0,0);
	}
	for (auto apt: nodes) {
	    double lat = apt->latitude_;
	    double lon = apt->longitude_;
	    int c1 = (int) (lon*2000/360+1000);
	    int c2 = (int) (-lat*1000/180+500-1);
	    for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
		    int c11 = std::max(0, std::min(c1+i,1999));
		    int c21 = std::max(0, std::min(c2+j,999));
		    world.getPixel(c11,c21) = cs225::HSLAPixel(0,1,0.5,1);
		}
	    }
	}
	return world;
    }

    cs225::PNG graph::plotEdges() {
	cs225::PNG world = plotNodes();
	for (auto aln: edges) {

	    /*
	    double a1c1 = ((aln->source_->longitude_)*2000.0/360+1000);
	    double a1c2 = (-(aln->source_->latitude_)*1000.0/180+500-1);
	    double a2c1 = ((aln->destination_->longitude_)*2000.0/360+1000);
	    double a2c2 = (-(aln->destination_->latitude_)*1000.0/180+500-1);

	    if (abs(a1c1-a2c1) <= 1000.0) {
		for (int i = (int) std::min(a1c1,a2c1); i <= (int) std::max(a1c1,a2c1); i++) {
		    int j = (int) ((a2c2-a1c2)/(a2c1-a1c1) * i - (a2c2-a1c2)/(a2c1-a1c1)*a1c1  + a1c2);
		    if (i<2000 && j<1000 && i>=0 && j>=0) {
		        world.getPixel(i,j) = cs225::HSLAPixel(100,1,0.5,1);
		    }
		}
	    } else {
		double negative, small, large, over, largey, smally;
		if (a1c1<a2c1) {
		    small = a1c1;
		    smally = a1c2;
		    large = a2c1;
		    largey = a2c2;
		    negative = a2c1-2000;
		    over = a1c1+2000;
		} else {
		    small = a2c1;
		    smally = a2c2;
		    large = a1c1;
		    largey = a1c2;
		    negative = a1c1-2000;
		    over = a2c1+2000;
		}
		for (int i = (int) large; i < 2000; i++) {
		    int j = (int) ((smally-largey)/(over-large) * i - (smally-largey)/(over-large)*large + largey);
		    if (i<2000 && j<1000 && i>=0 && j>=0) {
                        world.getPixel(i,j) = cs225::HSLAPixel(100,1,0.5,1);
                    }
		}
		for (int i = 0; i < (int) small; i++) {
		    int j = (int) ((smally-largey)/(small-negative) * i - (smally-largey)/(small-negative)*negative + largey);
		    if (i<2000 && j<1000 && i>=0 && j>=0) {
                        world.getPixel(i,j) = cs225::HSLAPixel(100,1,0.5,1);
                    }

		}
	    } 
	*/
	plotEdge(world, aln);
	}
	return world;
    }

    cs225::PNG graph::plotTopThree() {
	cs225::PNG world = plotEdges();
	std::vector<airport*> topThree = findTopThree();
	for (auto apt: topThree) {
	    double lat = apt->latitude_;
	    double lon = apt->longitude_;
	    int c1 = (int) (lon*2000/360+1000);
	    int c2 = (int) (-lat*1000/180+500-1);
	    for (int i = -5; i < 6; i++) {
		for (int j = -5; j < 6; j++) {
		    int c11 = std::max(0, std::min(c1+i,1999));
		    int c21 = std::max(0, std::min(c2+j,999));
		    world.getPixel(c11,c21) = cs225::HSLAPixel(250,1,0.5,1);
		}
	    }
	}
	return world;
    }

    void graph::plotEdge(cs225::PNG& world, airline* aln, double color) {
	double a1c1 = ((aln->source_->longitude_)*2000.0/360+1000);
        double a1c2 = (-(aln->source_->latitude_)*1000.0/180+500-1);
	double a2c1 = ((aln->destination_->longitude_)*2000.0/360+1000);
	double a2c2 = (-(aln->destination_->latitude_)*1000.0/180+500-1);

	if (abs(a1c1-a2c1) <= 1000.0) {
	    for (int i = (int) std::min(a1c1,a2c1); i <= (int) std::max(a1c1,a2c1); i++) {
	        int j = (int) ((a2c2-a1c2)/(a2c1-a1c1) * i - (a2c2-a1c2)/(a2c1-a1c1)*a1c1  + a1c2);
	        if (i<2000 && j<1000 && i>=0 && j>=0) {
		    world.getPixel(i,j) = cs225::HSLAPixel(color,1,0.5,1);
		}
	    }
	} else {
	    double negative, small, large, over, largey, smally;
	    if (a1c1<a2c1) {
		small = a1c1;
		smally = a1c2;
		large = a2c1;
		largey = a2c2;
		negative = a2c1-2000;
		over = a1c1+2000;
	    } else {
		small = a2c1;
		smally = a2c2;
		large = a1c1;
		largey = a1c2;
		negative = a1c1-2000;
		over = a2c1+2000;
	    }
	    for (int i = (int) large; i < 2000; i++) {
	        int j = (int) ((smally-largey)/(over-large) * i - (smally-largey)/(over-large)*large + largey);
		if (i<2000 && j<1000 && i>=0 && j>=0) {
                    world.getPixel(i,j) = cs225::HSLAPixel(color,1,0.5,1);
                }
	    }
	    for (int i = 0; i < (int) small; i++) {
	        int j = (int) ((smally-largey)/(small-negative) * i - (smally-largey)/(small-negative)*negative + largey);
		if (i<2000 && j<1000 && i>=0 && j>=0) {
                    world.getPixel(i,j) = cs225::HSLAPixel(color,1,0.5,1);
                }

	    }
        }
    }

    cs225::PNG graph::plotShortest(airport* a1, airport* a2) {
	cs225::PNG world = plotNodes();
	std::vector<airport*> vec = shortestPath(a1,a2);
	if (vec.size() < 1) {
	    return world;
	}
	airport* start = vec[0];
	for (size_t i = 1; i < vec.size(); i++){
	    plotEdge(world, new airline(start, vec[i]), 250.);
	    start = vec[i];
	}
	return world;
    }

    cs225::PNG graph::plotMST() {
	cs225::PNG world = plotEdges();
	vector<airline*> list = MST();
	for (auto i : list) {
	    plotEdge(world, i, 250.);
	}
	return world;
    }

// page rank

    vector<vector<double>> graph::constructMatrix(){
        size_t n = matrix.size();
        std::vector<double> row;
        std::vector<std::vector<double>> resultMatrix;
        
        for (size_t i=0; i < n; i++) {
           row.push_back(0);
        }
        for (size_t i=0; i < n; i++) {
            resultMatrix.push_back(row);
        }
        for (airline* dis: edges){
            int i = dis-> source_->id_;
            int j = dis-> destination_->id_;
            double weight = dis-> calculateDistance();

            resultMatrix[i][j] = weight;
            resultMatrix[j][i] = weight;
        }
        return resultMatrix;
    }

    vector<double> graph::matrixMutiplication(vector<double> rVector, vector<vector<double>> mMatrix){
        size_t n =matrix.size();
        vector<double> resultVector;
        for (size_t i = 0; i<n; i++) {
            double total = 0;
            for (size_t j = 0;j <n;j++ ){
                total += rVector[j]*mMatrix[i][j];
            }
            resultVector.push_back(total);
        }
        return resultVector;
    }

    vector<double> graph::normalization(vector<double> rVector){
        size_t n = rVector.size();
        double total = 0;
        vector<double> newVector;

        for (size_t i = 0;i<n;i++){
            total += abs(rVector[i]);
        }

        if (total == 0){
            return rVector;
        }

        for (size_t j =0; j<n; j++){
            newVector.push_back(rVector[j]/total);
        }
        return newVector;
    }

    vector<double> graph::pageRank(){
        size_t n= matrix.size();
        vector<vector<double>> resultedMatrix = constructMatrix();
        vector<double> resultV;
        for (size_t i=0;i<n;i++) {
            resultV.push_back(1);
        }
        resultV=normalization(resultV);
        for (int i = 0; i<10; i++) {
            resultV = matrixMutiplication(resultV,resultedMatrix);
            resultV = normalization(resultV);
        }

        return resultV;
    }

    airport* graph::findBest() {
	vector<double> grade = pageRank();
	double maxi = 0;
	size_t argm = 0;
	for (size_t i=0; i < grade.size(); i++) {
	    if (grade[i] > maxi) {
		maxi = grade[i];
		argm = i;
	    }
	}
	return nodes[argm];
    }

    std::vector<airport*> graph::findTopThree() {
	vector<double> grade = pageRank();
	double max1 = 0;
	double max2 = 0;
	double max3 = 0;
	size_t arg1 = 0;
	size_t arg2 = 0;
	size_t arg3 = 0;
	for (size_t i = 0; i < grade.size(); i++) {
	    if (grade[i] > max1) {
		max3 = max2;
		arg3 = arg2;
		max2 = max1;
		arg2 = arg1;
		max1 = grade[i];
		arg1 = i;
	    } else if (grade[i]>max2) {
		max3 = max2;
		arg3 = arg2;
		max2 = grade[i];
		arg2 = i;
	    } else if (grade[i]>max3) {
		max3 = grade[i];
		arg3 = i;
	    }
	}
	return {nodes[arg1], nodes[arg2], nodes[arg3]};
    }
