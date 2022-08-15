/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "shape.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Shape *stem;
    Shape *pistil; // center piece of flower
    Shape *leaf;               //modifed 2/24/2021, change those private var into ptrs, ex5

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    void draw(cs225::PNG* canvas) const;
    ~Flower();     //modifed 2/24/2021, add a destructor since we will new things and have to prevent memory leak, ex5

};
