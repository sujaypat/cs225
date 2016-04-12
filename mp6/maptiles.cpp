/**
* @file maptiles.cpp
* Code for the maptiles function.
*/

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource, vector<TileImage> const& theTiles){
	/**
	* @todo Implement this function!
	*/
	MosaicCanvas * scene = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

	vector< Point<3> > ayy_lmao;

	map<RGBAPixel,TileImage> Map;


	int m = 0;
	while(m < (int)theTiles.size()){
		TileImage tile = theTiles[m];
		RGBAPixel average = tile.getAverageColor();
		Point<3> currPix (average.red, average.green, average.blue);
		pair< RGBAPixel, TileImage > mapTile(average, tile);
		ayy_lmao.push_back(currPix);
		Map.insert(mapTile);
		m++;
	}

	KDTree<3> tree(ayy_lmao);

	for(int i = 0; i < theSource.getRows(); i++){
		for(int j = 0; j < theSource.getColumns(); j++){
			RGBAPixel avg = theSource.getRegionColor(i,j);
			Point<3> currPix(avg.red, avg.green, avg.blue);
			Point<3> memes = tree.findNearestNeighbor(currPix);
			RGBAPixel inception_avg(memes[0], memes[1], memes[2]);
			map< RGBAPixel, TileImage >::iterator it = Map.find(inception_avg);
			TileImage tile = it->second;
			scene->setTile(i, j, tile);
		}
	}

	return scene;

	// return NULL;
}
