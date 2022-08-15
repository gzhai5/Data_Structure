/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int row = theSource.getRows();
    int col = theSource.getColumns();

    MosaicCanvas *canvas = new MosaicCanvas(row, col);
    map<Point<3>, size_t> tile_image;
    vector<Point<3>> image_image;

    for (unsigned long i = 0; i < theTiles.size(); i++){
        Point<3> point = convertToXYZ(theTiles[i].getAverageColor());
        image_image.push_back(point);
        tile_image.insert(pair<Point<3>, size_t>(point,i));
    }
    KDTree<3> tree(image_image);
    for(int r = 0; r < row; r++){
      for(int c = 0; c < col; c++){
        Point<3> color_avg = convertToXYZ(theSource.getRegionColor(r, c));
        Point<3> color_avg_NN = tree.findNearestNeighbor(color_avg);
        int tile_tile = tile_image[color_avg_NN];
        canvas -> setTile(r, c, &theTiles[tile_tile]);
      }
    }
    return canvas;
}

