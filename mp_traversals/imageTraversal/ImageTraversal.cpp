#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}


double ImageTraversal::toler_check(const Point &point1, const Point &point2, const PNG & png){
  HSLAPixel p1 = png.getPixel(point1.x, point1.y);
  HSLAPixel p2 = png.getPixel(point2.x, point2.y);
  return calculateDelta(p1, p2);
}


/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(){
  /** @todo [Part 1] */
  traversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * trav, PNG png, double tolerance){
  traversal_ = trav;
  png_pic = png;
  toler = tolerance;
  curr = traversal_ -> peek();
  start_pt = curr;
  state = new int*[png_pic.width()];
  for (unsigned x = 0; x < png_pic.width(); x++){
    state[x] = new int[png_pic.height()];
    for (unsigned y = 0; y < png_pic.height(); y++){
      state[x][y] = 0;
    }
  }
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if (!traversal_ -> empty()) {
    //record the current location
    unsigned x_cord = curr.x;
    unsigned y_cord = curr.y;
    state[curr.x][curr.y] = 1;
    curr = traversal_ -> peek();
    traversal_ -> pop();
    bool flag = true;
    while (!traversal_ -> empty() && flag == true) {
      curr = traversal_ -> peek();
      if (state[curr.x][curr.y] == 1) {
        traversal_ -> pop();
      } 
      else{
        flag = false;
      }
    }
    if (x_cord != png_pic.width() - 1 && toler_check(start_pt, Point(x_cord + 1, y_cord), png_pic) < toler && state[x_cord+1][y_cord] == 0){
      traversal_ -> add(Point(x_cord + 1, y_cord));
    }
    if (y_cord != png_pic.height() - 1 && toler_check(start_pt, Point(x_cord, y_cord + 1), png_pic) < toler && state[x_cord][y_cord + 1] == 0){
      traversal_ -> add(Point(x_cord, y_cord + 1));
    }
    if (x_cord != 0 && toler_check(start_pt, Point(x_cord - 1, y_cord), png_pic) < toler && state[x_cord - 1][y_cord] == 0){
      traversal_ -> add(Point(x_cord - 1, y_cord));
    }    
    if (y_cord != 0 && toler_check(start_pt, Point(x_cord, y_cord - 1), png_pic) < toler && state[x_cord][y_cord - 1] == 0){
      traversal_ -> add(Point(x_cord, y_cord - 1));
    }
    if (!traversal_ -> empty()){
      curr = traversal_ -> peek();
    } 
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {     //provided in previous lab file
  /** @todo [Part 1] */     
  bool thisEmpty = false;
  bool otherEmpty = false;
  if (traversal_ == NULL) {
    thisEmpty = true;
  }
  if (other.traversal_ == NULL) {
    otherEmpty = true;
  }
  if (!thisEmpty){
    thisEmpty = traversal_ -> empty();
  }
  if (!otherEmpty){
    otherEmpty = other.traversal_ -> empty();
  }
  if (thisEmpty && otherEmpty){
    return false;
  } 
  else if ((!thisEmpty)&&(!otherEmpty)){
    return (traversal_ != other.traversal_);
  } 
  else{
    return true;
  }
}

