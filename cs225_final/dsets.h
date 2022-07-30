#pragma once
#include <vector>
using namespace std;

class DisjointSets
{
  public:
    void addelements(int);
    int find(int);
    void setunion(int,int);
    int size(int);

    vector<int> djs;
};