/* Your code here! */
#pragma once

#include <queue>
#include <stack>
#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"


using namespace cs225;
using namespace std;


class SquareMaze{
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir)const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG * drawMaze()const;
        PNG * drawMazeWithSolution();

    private:
        vector<int> square_vector;
        int m_width;
        int m_height;
        int dest;
        DisjointSets d_maze;
        vector<int> rht;
        vector<int> dwn;
};