#include "airport.h"
#include "airline.h"
#include "readFromFile.hpp"
#include <iostream>
#include <vector>
#include "graph.h"
#include "cs225/PNG.h"

int main() {
    // Importing the graph from .dat files
    graph globe("data/airports.dat", "data/airlines.dat");
    globe.print();

    // Plot all airports and airlines in the world andsave them to PNG
    cs225::PNG worldAirports = globe.plotNodes();
    cs225::PNG worldAirlines = globe.plotEdges();
    std::string const & fileName1 = "outputs/world-airports.png";
    std::string const & fileName2 = "outputs/world-airlines.png";
    worldAirports.writeToFile(fileName1);
    worldAirlines.writeToFile(fileName2);

    // Do Page Rank, figure out the answer, and plot the top three essential airports
    std::vector<airport*> rankings= globe.findTopThree();
    airport* first = rankings[0];
    std::cout << "The most important airport: ";
    first->print();
    std::cout << "The second most important airport: ";
    airport* second = rankings[1];
    second->print();
    std::cout << "The third most important airport: ";
    airport* third = rankings[2];
    third->print();
    cs225::PNG topThree = globe.plotTopThree();
    std::string const & fileName3 = "outputs/top-three.png";
    topThree.writeToFile(fileName3);

    // Plot shortest path from two chosen airports in the world
    std::string const & fileName4 = "outputs/shortest.png";
    cs225::PNG shortest = globe.plotShortest(globe.nodes[1341],globe.nodes[2095]);
    shortest.writeToFile(fileName4);

    // Plot a minimal spanning tree given by Kruskal's algorithm
    std::string const & fileName5 = "outputs/MST.png";
    cs225::PNG mst = globe.plotMST();
    mst.writeToFile(fileName5);

}
