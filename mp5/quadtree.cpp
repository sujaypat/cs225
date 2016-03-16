/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"
#include <cmath>
#include <iostream>

using namespace std;

Quadtree::Quadtree(){
    root = NULL;
}

Quadtree::Quadtree(const PNG & source, int resolution){
    buildTree(source, resolution);
}

Quadtree::Quadtree(Quadtree const & other){

    if (other.root == NULL){
        root = NULL;
        return;
    }
    root = copy(other.root);
}

Quadtree::QuadtreeNode * Quadtree::copy( QuadtreeNode *otherRoot){
    if (otherRoot == NULL){
        return NULL;
    }
    QuadtreeNode *res = new QuadtreeNode::QuadtreeNode(otherRoot);
    res->nwChild = copy(otherRoot->nwChild);
    res->neChild = copy(otherRoot->neChild);
    res->swChild = copy(otherRoot->swChild);
    res->seChild = copy(otherRoot->seChild);
    return res;
}

Quadtree::~Quadtree(){
    clearTree(root);
}

void Quadtree::clearTree( QuadtreeNode * & subRoot){

    if ( subRoot == NULL )
        return;


    clearTree(subRoot->nwChild);
    clearTree(subRoot->neChild);
    clearTree(subRoot->swChild);
    clearTree(subRoot->seChild);

    delete subRoot;
    subRoot = NULL;
}


Quadtree const & Quadtree::operator= (Quadtree const &other){

    if (root == other.root)
        return *this;

    clearTree(root);

    root = copy(other.root);
    return *this;
}

void Quadtree::buildTree (PNG const & source, int resolution){

    root = new QuadtreeNode(0, 0, resolution);

    buildTreeHelper (source, resolution, root);

}

void Quadtree::buildTreeHelper (PNG const & source, int resolution, QuadtreeNode *subRoot){

    if (resolution == 1){
        subRoot->element = *(source(subRoot->x, subRoot->y));
        return;
    }

    subRoot->nwChild = new QuadtreeNode(subRoot->x, subRoot->y, resolution/2);
    subRoot->neChild = new QuadtreeNode(subRoot->x + resolution/2, subRoot->y, resolution/2);
    subRoot->swChild = new QuadtreeNode(subRoot->x, subRoot->y + resolution/2, resolution/2);
    subRoot->seChild = new QuadtreeNode(subRoot->x + resolution/2, subRoot->y + resolution/2, resolution/2);

    buildTreeHelper(source, resolution/2, subRoot->nwChild);
    buildTreeHelper(source, resolution/2, subRoot->neChild);
    buildTreeHelper(source, resolution/2, subRoot->swChild);
    buildTreeHelper(source, resolution/2, subRoot->seChild);

    subRoot->element.red = (subRoot->nwChild->element.red + subRoot->neChild->element.red + subRoot->swChild->element.red + subRoot->seChild->element.red)/4;
    subRoot->element.green = (subRoot->nwChild->element.green + subRoot->neChild->element.green + subRoot->swChild->element.green + subRoot->seChild->element.green)/4;
    subRoot->element.blue = (subRoot->nwChild->element.blue + subRoot->neChild->element.blue + subRoot->swChild->element.blue + subRoot->seChild->element.blue)/4;
}

RGBAPixel Quadtree::getPixel (int x, int y) const{
    return getPixel(x, y, root);
}

RGBAPixel Quadtree::getPixel(int x, int y, QuadtreeNode *subRoot) const{
    if ((subRoot->x == x && subRoot->y == y && subRoot->res == 1) || (subRoot->nwChild == NULL))
        return subRoot->element;
    if (isInRange(x, y, subRoot->nwChild)){
        return getPixel(x, y, subRoot->nwChild);

    } else if (isInRange(x, y, subRoot->neChild)){
        return getPixel(x, y, subRoot->neChild);

    } else if (isInRange(x, y, subRoot->swChild)){
        return getPixel(x, y, subRoot->swChild);

    } else{
        return getPixel(x, y, subRoot->seChild);
    }
}

bool Quadtree::isInRange(int x, int y, QuadtreeNode *subRoot) const{
    int x_range = subRoot->x+subRoot->res;
    int y_range = subRoot->y+subRoot->res;

    return (x >= subRoot->x && x< x_range)&& (y >= subRoot->y && y < y_range);
}

PNG Quadtree::decompress() const{
    if (root == NULL)
        return *(new PNG());
    int resolution = root->res;
    PNG res(resolution, resolution);
    for (int i = 0; i < resolution; i++){
        for (int j = 0; j < resolution; j++){
            *(res(i, j)) = getPixel(i, j);
        }
    }
    return res;

}

void Quadtree::clockwiseRotate(){
   clockwiseRotate(root);
}

void Quadtree::clockwiseRotate(QuadtreeNode * subRoot){

    if (subRoot->nwChild == NULL)
        return;

    QuadtreeNode * temp = subRoot->nwChild;
    subRoot->nwChild = subRoot->swChild;
    subRoot->swChild = subRoot->seChild;
    subRoot->seChild = subRoot->neChild;
    subRoot->neChild = temp;

    subRoot->nwChild->x = subRoot->x;
    subRoot->nwChild->y = subRoot->y;

    subRoot->neChild->x = subRoot->x + subRoot->res/2;
    subRoot->neChild->y = subRoot->y;

    subRoot->swChild->x = subRoot->x;
    subRoot->swChild->y = subRoot->y + subRoot->res/2;

    subRoot->seChild->x = subRoot->x + subRoot->res/2;
    subRoot->seChild->y = subRoot->y + subRoot->res/2;

    clockwiseRotate(subRoot->nwChild);
    clockwiseRotate(subRoot->neChild);
    clockwiseRotate(subRoot->swChild);
    clockwiseRotate(subRoot->seChild);

}

void Quadtree::prune(int tolerance){
   prune(tolerance, root);
}

void Quadtree::prune(int tolerance, QuadtreeNode * subRoot){
    if (subRoot->nwChild == NULL)
        return;

    if (checkTolerance(subRoot, subRoot, tolerance)){
        clearTree(subRoot->nwChild);
        clearTree(subRoot->neChild);
        clearTree(subRoot->swChild);
        clearTree(subRoot->seChild);
        return;
    }

    prune(tolerance, subRoot->nwChild);
    prune(tolerance, subRoot->neChild);
    prune(tolerance, subRoot->swChild);
    prune(tolerance, subRoot->seChild);
}

bool Quadtree::checkTolerance(QuadtreeNode * subRoot, QuadtreeNode * avgRoot, int tol) const{
    if (subRoot->nwChild == NULL){
        return (difference(subRoot, avgRoot)<=tol);
    }
    return  (checkTolerance(subRoot->nwChild, avgRoot, tol) &&
                checkTolerance(subRoot->neChild, avgRoot, tol) &&
                checkTolerance(subRoot->swChild, avgRoot, tol) &&
                checkTolerance(subRoot->seChild, avgRoot, tol));
}


int Quadtree::difference(QuadtreeNode * a, QuadtreeNode * b) const{
    return (a->element.red - b->element.red) * (a->element.red - b->element.red)
	+ (a->element.green - b->element.green) * (a->element.green - b->element.green)
	+ (a->element.blue - b->element.blue) * (a->element.blue - b->element.blue);
}

int Quadtree::pruneSize(int tolerance) const{
    return pruneSize(tolerance, root);
}

int Quadtree::pruneSize(int tolerance, QuadtreeNode * subRoot) const{
    if (subRoot->nwChild == NULL)
        return 1;
    if (checkTolerance(subRoot, subRoot, tolerance)){
        return 1;
    }
    return pruneSize(tolerance, subRoot->nwChild)
	+ pruneSize(tolerance, subRoot->neChild)
	+ pruneSize(tolerance, subRoot->swChild)
	+ pruneSize(tolerance, subRoot->seChild);
}

int Quadtree::idealPrune(int numLeaves)const{
    return idealPrune(numLeaves, 255*255*3, 255*255*3);
}


int Quadtree::idealPrune(int numLeaves, int n, int interval) const{
    if (pruneSize(n) == numLeaves){
        while (pruneSize(n) == numLeaves)
            n--;
        return n+1;
    }
    if (pruneSize(n) < numLeaves){
        return idealPrune(numLeaves, n - interval/2, interval/2);
    }
    else{
        return idealPrune(numLeaves, n + interval/2, interval/2);
    }
}
