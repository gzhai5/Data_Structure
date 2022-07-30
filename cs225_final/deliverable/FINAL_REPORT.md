# CS 225 Final Project Final Report

## Leading Question

For our main goal, we want to solve the page rank problem. PageRank can be thought of as a model of user behavior. We assume there is a random surfer who is given a web page at random and keeps clicking on links, never hitting “back”, and he will keep doing this until he achieves a steady state. Thus given a graph, its nodes can be seen as websites, and its (directed) edges can be seen as links within the source webpage, and the weight on the edges determines probability of him clicking that link. The main problem for us is to determine the probability of the surfer browsing a given website after a period of time long enough to reach the steady state.

In this case, we can modify the use of Page Rank to airlines and airports. With the nodes being airports, edges being airlines, and weight being the distance of taking that flight. With page rank, we can figure out the importance of airports in the world.

## Dataset Aquisition and Processing

For our final project, we are going to use the dataset of ”OpenFlights”. Open flights is an open-source data set of flight routes and airports suggested in the given documents. We will download the .dat files which includes the data of airlines, airport names, cities, and countries from the OpenFlight website. For processing those data, We plan to use airports as nodes, airlines as edges, and use distance as the weight. More specifically, we will use the airport data to compute the distance between each airport and use the reciprocal of those distances as the weight.

The website of the above mentioned dataset is “https://openflights.org/data.html”. The download links for the two dat files are “https://raw.githubusercontent.com/jpatokal/openflights/master/data/airportsextended.dat” and “https://raw.githubusercontent.com/jpatokal/openflights/master/data/airlines.dat”.

## Graph Algorithms

- Graph Traversal (BFS).

    - input: an ptr of airport.

    - output: a vector saving the ptrs of airports that go through the BFS path.

    - Running Time: O(n).

- ShortestPath (Dijkstra).

    - input: two ptrs pointing to the source and destination airports.

    - output: airport* vector of the saving the order of aiprort in the shortest path.

    - Running Time: O(|V|log|V|).

- Minimal Spanning Tree (Kruskul)

    - input: a graph or no input

    - output: an airline vector or minimun cost

    - Running Time: O(m · log(m)).

- Page Rank Algorithm

    - input: a graph (might have multiple path components).

    - output: the steady state of Page rank.

    - Running Time: O(n^2 * p), where p is the number of iterations to reach steady state.

## Timeline

We uses the first 2 weeks for learning the algorthims and writing the code for them. The first things we finished are the ReadFromFile and our graph struture. Then we spent another week to finish up our BFS, ShortestPath, MST, and PageRank algorithms. For the third week, we wrote test files, debug the functions, and printed out images using our algorthims to make sure everything's functionality. Lastly, for the last week, we organized our code, deleted unnecessary files, finished our presentation powerpoint, and recorded the presentation.

## Development

The whole development process of what we have done each week as well as our plan for each week is saved in the "MEETING_LOG.md" file in the same directionary.

## Result

All of the output image files are placed in the outputs folder. Those PNG files show our classes (airline, airport) and the major algorithms (MST, shortest_path, pagerank). In addition, we come up our leading question through our main.cpp: "What is the most important airport on earth?" The answer is taht the most important airport in the world is FRA, Frankfurt Airport in Germany, which is detailed recorded in our presentation as well as the result after running the "finalproj". 

## Final Presentation

The final presentation video is uploaded to the mediaspace webiste, and here is the link: https://mediaspace.illinois.edu/media/t/1_ndbogxq8.