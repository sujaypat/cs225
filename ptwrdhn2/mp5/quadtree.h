/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
    /**
     * Big three
     */
    Quadtree();

    Quadtree(const PNG & source, int resolution);

    Quadtree(Quadtree const & other);

    ~Quadtree();


    /**
     *  Member functions
     */
    Quadtree const & operator= (Quadtree const &other);

    void buildTree (PNG const & source, int resolution);

    RGBAPixel getPixel (int x, int y) const;

    PNG decompress() const;

    void clockwiseRotate();

    void prune(int tolerance);

    int pruneSize(int tolerance) const;

    int idealPrune(int numLeaves)const;


	private:

	class QuadtreeNode{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child
		RGBAPixel element;  // the pixel stored as this node's "data"
        int x;
        int y;
        int res;

        QuadtreeNode(int xPos, int yPos, int resolution){
            x = xPos;
            y = yPos;
            res = resolution;
            nwChild = neChild = swChild = seChild = NULL;
        }

        QuadtreeNode(int xPos, int yPos, int resolution, PNG & source){
            x = xPos;
            y = yPos;
            res = resolution;
            nwChild = neChild = swChild = seChild = NULL;
            element = *(source(x,y));
        }

        QuadtreeNode(QuadtreeNode const * other){
            x = other->x;
            y = other->y;
            res = other->res;
            nwChild = neChild = swChild = seChild = NULL;
            element = other->element;
        }

	};

    void clearTree( QuadtreeNode * & subRoot);

    QuadtreeNode* copy(QuadtreeNode *otherRoot);

    void buildTreeHelper (PNG const & source, int resolution, QuadtreeNode *subRoot);

    RGBAPixel getPixel(int x, int y, QuadtreeNode *subRoot) const;

    bool isInRange(int x, int y, QuadtreeNode *subRoot) const;

    void clockwiseRotate(QuadtreeNode *subRoot);

    void prune(int tolerance, QuadtreeNode * subRoot);

    int difference(QuadtreeNode * a, QuadtreeNode * b) const;

    int pruneSize(int tolerance, QuadtreeNode * subRoot) const;

	QuadtreeNode* root;    // pointer to root of quadtree

    int idealPrune(int numLeaves, int n, int interval) const;

    bool checkTolerance(QuadtreeNode * subRoot, QuadtreeNode * avgRoot, int avg)const;

	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
