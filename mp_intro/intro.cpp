#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
cs225::PNG image;
image.readFromFile(inputFile);
cs225::PNG image2 = image;	
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      image2.getPixel(image.width()-x-1,image.height()-y-1) = image.getPixel(x, y);   
    }
  }
  image2.writeToFile(outputFile);
  //return image;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      if ((x < 0.5*width)&&(x > 0.6*y)){
        cs225::HSLAPixel & pixel=png.getPixel(x,y);
				pixel.h=15;
				pixel.s=0.6;
				pixel.l=.5;
				pixel.a=1.0;
      }
      if ((x > 0.5*width)&&(width - x <= 0.6*y)){
        cs225::HSLAPixel & pixel=png.getPixel(x,y);
				pixel.h=135;
				pixel.s=0.6;
				pixel.l=.5;
				pixel.a=1.0;
      }
      if ((x >= 0.5*width)&&(width - x > 0.6*y)){
        cs225::HSLAPixel & pixel=png.getPixel(x,y);
				pixel.h=345;
				pixel.s=0.2;
				pixel.l=.5;
				pixel.a=1.0;
      }
      if ((x <= 0.5*width)&&(x <= 0.6*y)){
        cs225::HSLAPixel & pixel=png.getPixel(x,y);
				pixel.h=225;
				pixel.s=0.2;
				pixel.l=.5;
				pixel.a=1.0;
      }
    }
  }    
  return png;
}
