#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "airport.h"
#include "airline.h"
#include "cs225/PNG.h"
#include "dsets.h"

#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;

using namespace std;

class graph {
    public:
        //page rank
        vector<vector<double>> constructMatrix();
        vector<double> matrixMutiplication(vector<double> rVector, vector<vector<double>> mMatrix);
        vector<double> normalization(vector<double> rVector);
        vector<double> pageRank();
	airport* findBest();
	vector<airport*> findTopThree();



        //graph structure
        graph();

        graph(const string & file_airport, const string & file_airline);

        void addAirport(airport* v);

        void removeAirport(airport* v);

        void addAirline(airline* other);

        void removeAirline(airline* v);




        std::vector<airline*> incidentAirline(airport* v );
        /**
         * this function is used to find all edges of one node 
         * (find all airlines that related with one airport, including going into the airport or going out of the airport)
         * the input of this function is a particular node (airport)
         * look it up in the matrix
         * if it is either the source or destination, then put the edge into the vector list
         * Meanwhile, caculate the number of both going into the airport or going out of the airport
         * 
         * Drawback: the order of edges (airlines) in the vector is unordered, 
         * which is hard to tell which part in the vector belongs to going into airport and going out of the airport
         * 
         * return the vector list that saves all the edges (airline) of one partiular node (airport)
         */



        bool areAdjacent(airline* v1, airline* v2);
        /**
         * this function can be used to know wheather 2 edges (airlines) are adjacent
         */ 



        std::vector<airport*> getneighborslist_of_node(airport *v);    //added by gzhai, for traversal function use, 4/28/2021
        /**
         * this function is used to find all neighbors of one node (find all airports that one particular airport can fly to)
         * treat this particular node (airport) as the source
         * look it up in the matrix
         * use the source to locate the row in matrix
         * and check whether the edge ptr points to a NULL or not
         * if pointing to NULL, which means no edges between 2 nodes (no airline through the source airport to destination airport)
         * if not pointing to NULL, which means having an edgesbetween 2 nodes (have airline through the source airport to destination airport)
         * save all the destination nodes (detination airports) into a list and return it
         */      





        std::vector<std::string> BFS_path(airport* v);
        /**
         * this function is exactly same as the BFS fcn
         * however, it has a return value: a vector that saves all the names of airports of our path in the traversal order
         */



        std::vector<airport*> shortestPath(airport *source, airport *destination);    
        /**
         * this function return the shortest path from one node to another
         * get reference from the course website:  https://courses.engr.illinois.edu/cs225/sp2021/resources/dijkstra/
         * Psedocode:
         * "Dijkstra(Graph, source, destination):
         *      initialize distances                  // initialize tentative distance value
                initialize previous                   // initialize a map that maps current node -> its previous node
                initialize priority_queue             // initialize the priority queue
                initialize visited

                while the top of priority_queue is not destination:
                        get the current_node from priority_queue
                        for neighbor in current_node's neighbors and not in visited:
                                if update its neighbor's distances:
                                        previous[neighbor] = current_node
                                        save current_node into visited

                extract path from previous
                return path and distance
         *        
         * inputs of the fcn is the source airport and destination airport
         */



        


        cs225::PNG plotNodes();
	cs225::PNG plotEdges();
	cs225::PNG plotTopThree();
	void plotEdge(cs225::PNG& png, airline* aln, double color = 100.);
	cs225::PNG plotShortest(airport* a1, airport* a2);
	cs225::PNG plotMST();



        vector<airport*> nodes;
        vector<airline*> edges;
        vector<vector<airline*>> matrix;        //Vector of Vectors is a two-dimensional vector with a variable number of rows where each row is vector.

	void print();

        //  mutable unordered_map<airport, unordered_map<airport, airline>> adjacency_Matrix;

        // bool weighted;
        // bool directed;

        void clear();

	~graph();

        // const static airport InvalidNode;
        // const static airline InvalidEdge;
        // const static int InvalidWeight;
        // const static string InvalidLabel;

    class subset {
        //represent a subset for union-find for MST
        public:
            int parent;
            int rank;
    };

  
    double KruskalMST(graph & g);
    vector<airline*> MST();

    private:
        //below are all helper fcns or unused fcns

        double calculateDistance(double latitude1,double longitude1,double latitude2,double longitude2);
        double calculateDistance(airport* source, airport* destination);       //copied by gzhai, 5/6/2021
        /**
         * this 2 fcns are copied from the airline file
         * just be convenient to calculate the edge weight here in this graph file
         */




        double find_shortest(vector<double> distances);  //added by gzhai5, thought as a helper fcn for mst, 5/2/2021
        /**
         * this function return the smallest value in a vector
         * the type in the vector and the return type is double
         */




        void BFS(airport* v);      //added by gzhai, as a traversal function, 4/28/2021
        /**
         * this function is void function that go through all the nodes
         * using BFS algorthim
         * create a list to save visited nodes
         * and create a queue to save frontier
         */
};
