# Meeting Log

This file acts as the meeting log of all major meetings throughout this semester. It also acts as the "development" file required for grading. Note that when moving the original file in this folder when organizing, we accidentally lost out commit history. (The original file was ../MEETING_LOG.md with respect to the current location). Its commit history can be seen in the overall commit history. Sorry for the invenience this might cause.

## Meeing at April 12

Today is our first meeting. We discussed the goals we would like to achieve in the following weeks, the workload distribution for this week, and the files we will create.

### What we need
  A class of “graph”
	A subclass of edge 
  A subclass of nodes 
	read airport data
	read airline data
	Traversal
	MST
	PG Rank
calculate distance ( latitude/longtitude → distance, i.e. weight)  peilinh2


### Work distribution

yikait2: Write functions for reading data from the two .dat files

qc15: Compose the structures of the class Graph
 
gzhai5: Traversal.

peilinh2: Translate the coordinates of the departure and arrival airports to distances.

### Files we will create
Graph.h
Graph.cpp

Traversal.h
Traversal.cpp
DFS.h
DFS.cpp

## Meeing at April 19

Today is our second meeting. We discussed the work progress everyone is on for last week's work, the goals we would like to achieve in the following weeks,and the workload distribution for this week, and the files we will create.

### What we need
  A class of “graph”
	A subclass of edge 
  A subclass of nodes 
	read airport data
	read airline data
	Traversal
	MST
	PG Rank
Minimal Spanning Tree
calculate distance ( latitude/longtitude → distance, i.e. weight)  peilinh2


### Work distribution

yikait2: more on "read from file" and more tests in main.cpp

qc15: Finish graph implementation by Wednesday.Brainstorm ways for matrix calculation implementation.
 
gzhai5: Finish Traversal by Wednesday

peilinh2: Start working on Minimal Spanning Tree.

### Files we will create
minimalSpanningTree.cpp (maybe)
minimalSpanningTree.h (maybe)
 
MEETING_LOG.md

## Meeing at April 26

Today is our third meeting. We discussed the code we have done so far and planned for the next several weeks' distributions.

### What we need
  A class of “graph”
	A subclass of edge 
  A subclass of nodes 
	read airport data
	read airline data
	Traversal
	MST
	PG Rank
Minimal Spanning Tree
calculate distance ( latitude/longtitude → distance, i.e. weight)  peilinh2


### Work distribution

yikait2: more tests in main.cpp

qc15: Finish graph by this Thursday
 
gzhai5: test on traversal, shortestpath by this Sat

peilinh2: Minimal Spanning Tree and test its functions, shortestpath by this Sat

### Files we will create
minimalSpanningTree.cpp 
minimalSpanningTree.h 
shortestpath 
MEETING_LOG.md

## Meeting at May 3

Today we talked about our progress throuout the last week. Now, our BFS and MST are almost done, but tests are not conducted.

We also talked about the splitting of tests and the delivery of final results, which leads to some minor changes of the structure. 

### Work Distribution

qc15: Page rank and its tests

gzhai5: finishing BFS and its tests

peilinh2: finishing MST and its tests

yikait2: work on final diliverables, including plotting of the airport and possible slides structures

## Meeting at May 10

Today we talked about what content we miss and what we should add to finish our final project and prepare for our presentation.

### Work Distribution

In slides:
Test Conducted in Slides
Running time for Page Rank

In code:
Clean up
Add  more tests

In README:
The location of all major code, data, and results. 
Full instructions on how to build and run your executable,
Full instructions how to build and run your test suite, including a general description on what tests you have created.

In report:
Modify the proposal into Result
