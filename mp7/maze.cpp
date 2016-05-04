#include "maze.h"

SquareMaze::SquareMaze(){}
void SquareMaze::makeMaze(int width, int height){}
bool SquareMaze::canTravel(int x, int y, int dir) const{
	return true;
}
void SquareMaze::setWall (int x, int y, int dir, bool exists){}
vector <int> SquareMaze::solveMaze(){
	return vector<int>();
}
PNG * SquareMaze::drawMaze() const{
	return new PNG();
}
PNG * SquareMaze::drawMazeWithSolution(){
	return new PNG();
}