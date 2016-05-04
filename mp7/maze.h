/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include <iostream>
#include "png.h"
#include <map>
#include <queue>
#include <stack>
using namespace std;

class SquareMaze {

	public:
		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall (int x, int y, int dir, bool exists);
		vector <int> solveMaze();
		PNG * drawMaze() const;
		PNG * drawMazeWithSolution();

};

#endif
