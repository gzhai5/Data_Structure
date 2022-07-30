#include "../cs225/catch/catch.hpp"

#include "../airport.h"
#include "../airline.h"
#include "../graph.h"

#include <utility>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <numeric>
#include <vector>





using namespace cs225;

/**testcase for test.cpp run correctly**/
TEST_CASE("test.cpp") {
    string test_text = "cs225";

    REQUIRE( test_text == "cs225" );
}



/**testcase for bfs**/
TEST_CASE("BFS maintains the BFS ordering") {
    graph test_graph1("data/airport-zero.dat", "data/airline-zero.dat");
    test_graph1.addAirport(new airport(1, "1", 0, 0));
    test_graph1.addAirport(new airport(2, "2", -0.5, -0.5));
    test_graph1.addAirport(new airport(3, "3", 0.5, -0.5));
    test_graph1.addAirport(new airport(4, "4", -1, -1));
    test_graph1.addAirport(new airport(5, "5", 1, -1));
    test_graph1.addAirport(new airport(6, "6", 0, -1));
    test_graph1.addAirline(new airline(test_graph1.nodes[0], test_graph1.nodes[1]));
    test_graph1.addAirline(new airline(test_graph1.nodes[0], test_graph1.nodes[2]));
    test_graph1.addAirline(new airline(test_graph1.nodes[1], test_graph1.nodes[3]));
    test_graph1.addAirline(new airline(test_graph1.nodes[2], test_graph1.nodes[4]));
    test_graph1.addAirline(new airline(test_graph1.nodes[1], test_graph1.nodes[5]));
    test_graph1.addAirline(new airline(test_graph1.nodes[2], test_graph1.nodes[5]));


    /**
     *                                          1
     *                                         / \
     *                                        2   3
     *                                       / \ / \
     *                                      4   6   5
     * **/


    // airport* start = test_graph1.nodes.front();
    vector<std::string> test_graph1_trav_path = test_graph1.BFS_path(test_graph1.nodes[0]);

    // cout<<"size of trav_path is"<<test_graph1_trav_path.size()<<endl;

    REQUIRE( test_graph1_trav_path[0] == "1" );
    REQUIRE( test_graph1_trav_path[1] == "2" );
    REQUIRE( test_graph1_trav_path[2] == "3" );
    REQUIRE( test_graph1_trav_path[4] == "4" );
}


/**testcase for find_neighbors**/
TEST_CASE("can get all neighbors of a node (airport)") {
    graph test_graph2("data/airport-zero.dat", "data/airline-zero.dat");
    test_graph2.addAirport(new airport(1, "1", 0, 0));
    test_graph2.addAirport(new airport(2, "2", -1, -1));
    test_graph2.addAirport(new airport(3, "3", 0, -1));
    test_graph2.addAirport(new airport(4, "4", 1, -1));
    test_graph2.addAirline(new airline(test_graph2.nodes[0], test_graph2.nodes[1]));
    test_graph2.addAirline(new airline(test_graph2.nodes[0], test_graph2.nodes[2]));
    test_graph2.addAirline(new airline(test_graph2.nodes[0], test_graph2.nodes[3]));

    // for (size_t i = 0; i < 4; i++){

    //     for (size_t j = 0; j < 4; j++){
    //         cout<<test_graph2.matrix[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }

    /**
     *                   1
     *                  /|\
     *                 2 3 4              
     * **/

    vector<airport*> neighbor_list = test_graph2.getneighborslist_of_node(test_graph2.nodes[0]);

    REQUIRE( neighbor_list[0] -> name_ == "2" );
    REQUIRE( neighbor_list[1] -> name_ == "3" );
    REQUIRE( neighbor_list[2] -> name_ == "4" );

}




/**testcase for shortest_path**/
TEST_CASE("shortest path is correct") {
    graph test_graph3("data/airport-zero.dat", "data/airline-zero.dat");
    test_graph3.addAirport(new airport(1, "1", 0, 0));
    test_graph3.addAirport(new airport(2, "2", -1, 0));
    test_graph3.addAirport(new airport(3, "3", 1.5, 2.7));
    test_graph3.addAirport(new airport(4, "4", 1, 0));
    test_graph3.addAirport(new airport(5, "5", 3, 0));
    test_graph3.addAirport(new airport(6, "6", -2, 0));
    test_graph3.addAirport(new airport(7, "7", 2, 0));
    test_graph3.addAirline(new airline(test_graph3.nodes[0], test_graph3.nodes[1]));
    test_graph3.addAirline(new airline(test_graph3.nodes[1], test_graph3.nodes[5]));
    test_graph3.addAirline(new airline(test_graph3.nodes[0], test_graph3.nodes[2]));
    test_graph3.addAirline(new airline(test_graph3.nodes[0], test_graph3.nodes[3]));
    test_graph3.addAirline(new airline(test_graph3.nodes[3], test_graph3.nodes[6]));
    test_graph3.addAirline(new airline(test_graph3.nodes[6], test_graph3.nodes[4]));

    /**
     *                 6---2---1---4---7---5
     *                          \         /
     *                           \       /
     *                            \     /
     *                             \   /
     *                               3
     * **/

    std::vector<airport*> shortest_path = test_graph3.shortestPath(test_graph3.nodes[5], test_graph3.nodes[4]);

    REQUIRE( shortest_path[0] -> name_ == "6" );
    REQUIRE( shortest_path[1] -> name_ == "2" );
    REQUIRE( shortest_path[2] -> name_ == "1" );
    REQUIRE( shortest_path[3] -> name_ == "4" );
    REQUIRE( shortest_path[4] -> name_ == "7" );
}


// page rank test case
TEST_CASE("find best is correct") {
    graph test_graph4("data/airport-zero.dat", "data/airline-zero.dat");
    test_graph4.addAirport(new airport(1, "1", 1, 2));
    test_graph4.addAirport(new airport(2, "2", 3, 4));
    test_graph4.addAirport(new airport(3, "3", 4, 1));
    test_graph4.addAirport(new airport(4, "4", 1, 4));
    test_graph4.addAirport(new airport(5, "5", -1, -1));
    test_graph4.addAirport(new airport(6, "6", -17, -12));
    test_graph4.addAirport(new airport(7, "7", 5, 1));
    test_graph4.addAirline(new airline(test_graph4.nodes[0], test_graph4.nodes[1]));
    test_graph4.addAirline(new airline(test_graph4.nodes[1], test_graph4.nodes[5]));
    test_graph4.addAirline(new airline(test_graph4.nodes[0], test_graph4.nodes[2]));
    test_graph4.addAirline(new airline(test_graph4.nodes[0], test_graph4.nodes[3]));
    test_graph4.addAirline(new airline(test_graph4.nodes[3], test_graph4.nodes[4]));

    /**
     *                 6---2---1---4---5
     *                          \     /
     *                           \   /
     *                             3
     * **/

    airport* page_rank = test_graph4.findBest();

    REQUIRE( page_rank->name_== "6" );

   
}




/**testcase for MST**/
TEST_CASE("Kruskal's MST is correct. ") {
    graph test_graph5("data/airport-zero.dat", "data/airline-zero.dat");
    test_graph5.addAirport(new airport(1, "A", 1, 2));
    test_graph5.addAirport(new airport(2, "B", 2, 2));
    test_graph5.addAirport(new airport(3, "C", 3, 2));
    test_graph5.addAirport(new airport(4, "D", 2, 1));
    test_graph5.addAirport(new airport(5, "E", 3, 1));
    test_graph5.addAirport(new airport(6, "F", 5, 2));
    test_graph5.addAirline(new airline(test_graph5.nodes[0], test_graph5.nodes[1]));
    test_graph5.addAirline(new airline(test_graph5.nodes[1], test_graph5.nodes[2]));
    test_graph5.addAirline(new airline(test_graph5.nodes[1], test_graph5.nodes[3]));
    test_graph5.addAirline(new airline(test_graph5.nodes[3], test_graph5.nodes[4]));
    test_graph5.addAirline(new airline(test_graph5.nodes[2], test_graph5.nodes[5]));
    test_graph5.addAirline(new airline(test_graph5.nodes[2], test_graph5.nodes[4]));
    test_graph5.addAirline(new airline(test_graph5.nodes[0], test_graph5.nodes[3]));
//    double cost=test_graph5.KruskalMST(test_graph5);
//    REQUIRE( cost == 667.6822249828 );

    vector<airline*> mst_path=test_graph5.MST();
    REQUIRE( mst_path[0] ->source_->id_ == 2 );
    REQUIRE( mst_path[0] ->destination_->id_ == 4 );
    REQUIRE( mst_path[1] ->source_->id_ == 1 );
    REQUIRE( mst_path[1] -> destination_->id_ == 3 );
    REQUIRE( mst_path[2] ->source_->id_ == 0 );
    REQUIRE( mst_path[2] -> destination_->id_ == 1 );
    REQUIRE( mst_path[3] ->source_->id_ == 1 );
    REQUIRE( mst_path[3] -> destination_ ->id_== 2 );
    REQUIRE( mst_path[4] ->source_->id_ == 2 );
    REQUIRE( mst_path[4] -> destination_ ->id_== 5 );
//          1   1    2
 //       0---1---2------5
 //       \   |   |     
 //      2 \  |1  |1   
 //         \ | 1 |  
 //           3---4
    

}




// TEST_CASE("read from file tests") {
//     graph test("data/airports.dat", "data/airlines.dat");
//     REQUIRE(test.nodes.size() == test.matrix.size());
//     REQUIRE(test.nodes.size() == test.matrix[0].size());
// }

