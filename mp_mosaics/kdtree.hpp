/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    bool result;
    if (first[curDim] == second[curDim]) {
      result = first < second;
    } 
    else if (first[curDim] < second[curDim]) {
      result = true;
    }
    else{
      result = false;
    }
    return result;    
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double dist_tar_cur = 0;
    double dist_tar_pot = 0;

    for (int i = 0; i < Dim; i++){
      dist_tar_cur += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      dist_tar_pot += (target[i] - potential[i]) * (target[i] - potential[i]); 
    }

    if (dist_tar_cur > dist_tar_pot){
      return true;
    }
    if (dist_tar_pot == dist_tar_cur){
      return currentBest > potential;
    }
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty()){
      root = NULL;
    }
    else{ 
      vector<Point<Dim>> points(newPoints);
      int dimension = 0;
      int start = 0;
      int end = points.size() - 1;      
      buildTree(points, dimension, root, start, end);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  CopyTree(root, other -> root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  clear(root);
  CopyTree(root, rhs -> root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int dim = 0;
    Point<Dim> x = root -> point;
    findNearestNeighbor(query, x, root, dim);
    return x;
}

