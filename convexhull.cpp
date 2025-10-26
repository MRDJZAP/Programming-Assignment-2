/**
 * @file convexhull.cpp
 * @description Implementation of methods used for computing convex hull using
 *              Graham scan algorithm
 *              https://en.wikipedia.org/wiki/Graham_scan
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE MUST BE SUBMITTED
**/

#include "convexhull.h"
#include <cmath>

/***************************************************
* IF YOU WISH TO DEFINE YOUR OWN CUSTOM FUNCTIONS, *
* ADD THEM HERE                                    *
***************************************************/

/**
 * POST: retuns the distance between two points
 */
double dist(pair<double, double> p1, pair<double, double> p2) {
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + 
           (p1.second - p2.second) * (p1.second - p2.second));
}


/**
 * PRE: both points must be in the first quadrant
 * POST: returns the polar angle between two points
 */
double getAngle(pair<double, double> p1, pair<double, double> p2) {
    // return pi/2 if x values are the same
    // note (std::atan(1.0) * 4.0) = pi
    if (p1.first == p2.first) {
        return (std::atan(1.0) * 4.0) / 2.0;
    }
    
    double aX = p2.first - p1.first;
    double aY = p2.second - p1.second;
    double angle = std::atan(aX/aY);

    // convert to polar angle
    if (angle < 0.0) {
        return (std::atan(1.0) * 4.0) + angle;
    }

    return angle;
}

/**
 * PRE: i >= 0
 * POST: returns the index in which points to the smallest angle of the points in v
 * 
 * NOTE: does not modify the v
 */
int findMinIndex(int index, pair<double, double> refPoint, vector<pair<double, double>>& v) {
    int minIndex = index;
    double minAngle = getAngle(refPoint, v[index]);

    for (int i = index + 1; i < v.size(); i++) {
        double currAngle = getAngle(refPoint, v[i]);
        if (currAngle < minAngle) {
            minAngle = currAngle;
            minIndex = i;
        }
    }

    return minIndex;
}

/**
 * PRE: v at least contains one element
 * POST: sorts the vector v in increasing order by the angle with the reference point v[0]
 */
void selectionSort(vector<pair<double, double>>& v) {
    pair<double, double> refPoint = v[0];
    for (int i = 1; i < v.size() - 1; i++) {
        int minIndex = findMinIndex(i, refPoint, v);

        // swap
        pair<double, double> temp = v[i];
        v[i] = v[minIndex];
        v[minIndex] = temp;
    }
}


/**
 * Uses a sorting algorithm of your choice(must be fully implemented by you)
 * to sort the points in v to satisfy the following criteria:
 * 1. v[0] must contain the point with the smallest y-coordinate.
 *      If multiple points have the same smallest y-coordinate, v[0]
 *      must contain the one among those with the smallest x-coordinate.
 * 2. The remaining indices i contain the points, sorted in increasing order
 *      by the angle that the point forms with v[0] and the x-axis. That is,
 * 	one of the legs of the angle is represened by the line through v[0] and
 *	v[i], and the other is the x-axis.
 * NOTE: "smallest" y-coordinate is actually closest to the TOP of a PNG image.
**/
void SortByAngle(vector<pair<double, double>>& v) {
	// find the point with smallest y-coordinate or x if identical
    int minIndex = 0;
    pair<double, double> minPoint = v[0];

    for (unsigned int i = 1; i < v.size(); i++) {
        if (v[i].second < minPoint.second || (v[i].second == minPoint.second && v[i].first < minPoint.first)) {
            minPoint = v[i];
            minIndex = i;
        } 
    }    
    // swap that smallet point with the index 0
    if (minIndex != 0){
        pair<double, double> temp = v[0];
        v[0] = minPoint;
        v[minIndex] = temp;
    }
    // sort starting from index 1 using the helper get angle function to compare angles	
    selectionSort(v);
}

/**
 * Determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
**/
bool CCW(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3) {
    double v = p1.first * (p2.second - p3.second) + 
               p2.first * (p3.second - p1.second) + 
               p3.first * (p1.second - p2.second);

    // colinear point
    if (v == 0) {
        return false;
    } 

    return v > 0;
}

/**
 * Returns a vector of points representing the convex hull of v
 * if c is the vector representing the convex hull, then c[k], c[k+1]
 * is an edge in the convex hull, for all k in 0 to n-1, where n is the
 * number of points in the hull. c[n-1],c[0] is also an edge in the hull.
 * Note that only the endpoints of a colinear sequence will belong in the hull.
 * The returned vector should be a subset of v
 * Input: v - a vector of points in arbitrary order
**/
vector<pair<double, double>> GetConvexHull(vector<pair<double, double>>& v) {
	vector<pair<double, double>> hull;

    // // checking for valid hull
    // if (v.size() < 3) {
    //     return hull;
    // }

    // SortByAngle(v);

    // // push the first ref point
    // hull.push_back(v[0]);

    // // find the convex hull





	return hull;
}
