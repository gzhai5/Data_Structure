
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png_pic;
  png_pic.readFromFile("part3_originial.png");
  FloodFilledImage image(png_pic);  
  DFS dfs(png_pic, Point(0,50), 0.2);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill(dfs, rainbow);
  BFS bfs(png_pic, Point(100, 50), 0.4);
  HSLAPixel color(156, 1.0, 0.47);
  MyColorPicker my_color_picker;
  image.addFloodFill(bfs, my_color_picker);
  Animation animation = image.animate(1600);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
