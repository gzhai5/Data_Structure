/* Your code here! */
#include "dsets.h"




using namespace std;


/*Creates n unconnected root nodes at the end of the vector*/
void DisjointSets::addelements(int num){
    for (int i = 0; i < num; i++){
        elem_vector.push_back(-1);
    }
}



/*This function should compress paths and works as described in lecture.*/
int DisjointSets::find(int elem){
    if (elem_vector[elem] < 0){
        return elem;
    }
    else{
        int result = find(elem_vector[elem]);
        elem_vector[elem] = result;
        return result;
    } 
}



/*This function should be implemented as union-by-size.
  That is, when you setunion two disjoint sets, the smaller 
  (in terms of number of nodes) should point at the larger. 
  This function works as described in lecture, except that 
  you should not assume that the arguments to setunion are 
  roots of existing uptrees.*/
void DisjointSets::setunion(int a, int b){
    a = find(a);
    b = find(b);
    int size_new = elem_vector[a] + elem_vector[b];
    int x = elem_vector[a];
    int y = elem_vector[b];
    if (a >= b){
        elem_vector[a] = b;
        elem_vector[b] = size_new;
    }
    else{
        elem_vector[a] = size_new;
        elem_vector[b] = a;
    }
}




/*This function should return the number of nodes in the up-tree containing the element*/
int DisjointSets::size(int elem){
    while (elem_vector[elem] >= 0){
        elem = elem_vector[elem];
    }
    int result = (-1) * elem_vector[elem];
    return result;
}

