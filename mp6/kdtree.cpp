/**
* @file kdtree.cpp
* Implementation of KDTree class.
*/
#include <iostream>
#include <math.h>

using namespace std;
template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const{
	/**
	* @todo Implement this function
	*/
	return (first[curDim] == second[curDim]) ? first < second : first[curDim] < second[curDim];
}

template<int Dim>
int KDTree<Dim>::distance(const Point<Dim> & target, const Point<Dim> & currentBest) const{
	int sum = 0;
	for(int i = 0; i < Dim; i++){
		sum += pow((currentBest[i] - target[i]), 2);
	}
	return sum;
}
template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const{
	/**
	* @todo Implement this function!
	*/
	int sum1 = 0, sum2 = 0;
	for(int i = 0; i < Dim; i++){
		sum1 += pow((currentBest[i] - target[i]), 2);
		sum2 += pow((potential[i] - target[i]), 2);
	}
	if(sum1 < sum2) return false;
	else if(sum1 > sum2) return true;
	else return potential < currentBest;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints){
	/**
	* @todo Implement this function!
	*/
	dimension = Dim;
	points = newPoints;
	if(points.size() != 0) build(points, 0, 0, newPoints.size() - 1);
}
template<int Dim>
void KDTree<Dim>::build(vector< Point<Dim> > & newPoints, int curDim, int lo, int hi){
	if(lo == hi) return;
	int dim = curDim % dimension;
	int mid = ((lo + hi) / 2);

	select(newPoints, lo, hi, mid, dim);
	if(lo < mid) build(newPoints, dim + 1, lo, mid - 1);
	if(hi > mid)build(newPoints, dim + 1, mid + 1, hi);
}

template<int Dim>
void KDTree<Dim>::select(vector< Point<Dim> > & newPoints, int lo, int hi, int n, int curDim){
	while(lo != hi){
        int pivot = partition(newPoints, lo, hi, n, curDim);
        if (pivot == n) return;
        else if (n < pivot) hi = pivot - 1;
        else lo = pivot + 1;

    }
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> > & newPoints, int low, int high, int pivotIndex, int curDim){
	Point<Dim> pivotValue = newPoints[pivotIndex];
	Point<Dim> temp = newPoints[high];
	newPoints[high] = newPoints[pivotIndex];
	newPoints[pivotIndex] = temp;
	int temp_low = low;
	for(int i = low; i < high; i++){
		if(smallerDimVal(newPoints[i], pivotValue, curDim) || newPoints[i] == pivotValue){
			temp = newPoints[i];
			newPoints[i] = newPoints[temp_low];
			newPoints[temp_low] = temp;
			temp_low++;
		}
	}
	temp = newPoints[temp_low];
	newPoints[temp_low] = newPoints[high];
	newPoints[high] = temp;
	return temp_low;
}
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const{
	/**
	* @todo Implement this function!
	*/
	return find_helper(query, 0, points.size() - 1, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::find_helper(const Point<Dim> & query, int lo, int hi, int curDim) const{
	int curr_axis = curDim % Dim;
	int mid = (lo + hi) / 2;
	bool in_left = false;
	Point<Dim> tree1;
	Point<Dim> tree2;
	int bst_distance;
	if(lo >= hi){
		return points.at(mid);
	}
	else{
		if(smallerDimVal(query, points.at(mid), curr_axis)){
			//left subtree
			tree1 = find_helper(query, lo, mid - 1, curDim + 1);
			in_left = true;
		}
		else if(!(smallerDimVal(query, points.at(mid), curr_axis))){
			//right subtree
			tree1 = find_helper(query, mid + 1, hi, curDim + 1);
		}
	}

	if(shouldReplace(query,tree1,points.at(mid))){
		tree1 = points.at(mid);
	}

	bst_distance = distance(query,tree1);
	int dim_dist = pow((query[curr_axis] - points.at(mid)[curr_axis]), 2);
	if(dim_dist <= bst_distance){

		if(in_left == false) tree2 = find_helper(query, lo, mid - 1, curDim + 1);
		else tree2 = find_helper(query, mid + 1, hi, curDim + 1);
		if(shouldReplace(query, tree1, tree2)) tree1 = tree2;
	}
	return tree1;
}
