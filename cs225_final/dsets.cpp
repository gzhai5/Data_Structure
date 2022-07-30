/* Your code here! */

#include "dsets.h"
#include <iostream>
using namespace std;

void DisjointSets::addelements(int num){
  for(int i=0;i<num;i++){
    djs.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if(elem > (int)djs.size()){
    return -1;
  }

  else if(djs[elem] < 0){
    return elem;
  }
 
  else{
  djs[elem] = find(djs[elem]);
  return find(djs[elem]);
  }

}


void DisjointSets::setunion(int a ,int b){
int finda=find(a);
int findb=find(b);
if(finda==findb) {
    return;
}
  if(djs[finda] > djs[findb]){
    djs[findb] += djs[finda];
    djs[finda] = findb;
  }
  else{	  
  djs[finda]+= djs[findb];
  djs[findb] = finda;
  }


}

int DisjointSets::size(int elem){
  return djs[find(elem)]*-1;
}