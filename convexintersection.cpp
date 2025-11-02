/**
 * @file        convexintersection.cpp
 * @description Implementation of methods used for computing convex intersection using
 *              Sutherland-Hodgman algorithm
 *              https://en.wikipedia.org/wiki/Sutherland�Hodgman_algorithm
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE MUST BE SUBMITTED
**/

#include "convexintersection.h"

/***************************************************
* IF YOU WISH TO DEFINE YOUR OWN CUSTOM FUNCTIONS, *
* ADD THEM HERE                                    *
***************************************************/

/**
 * Checks if two line segments are pararel by comparing their slopes.
 */
bool isPararel(pair<double, double> p1, pair<double, double> p2, pair<double, double> ip1, pair<double, double> ip2) {
	return (p2.second - p1.second)/(p2.first - p1.first) == (ip2.second - ip1.second)/(ip2.first - ip1.first);
}

/**
 * Determines whether a point p1 is inside or outside
 * of a line segment defined by sp1 and sp2
 * sp1 and sp2 should be consistently provided
 * from the convex hull algorithm such that the edges
 * are listed in a CCW direction
 * p1 belongs to the subject polygon
 * sp1 and sp2 belong to the clipping polygon
**/
bool Inside(pair<double, double> p1, pair<double, double> sp1, pair<double, double> sp2) {
	double R = (p1.first - sp1.first) * (sp2.second - sp1.second) - (p1.second - sp1.second) * (sp2.first - sp1.first);

	return R > 0;
}

/**
 * computes the point of intersection between the line segment
 * defined by s1 and s2, and the infinite line defined by
 * i1 and i2.
 * Assume that this will only be called when the intersection exists.
**/
pair<double, double> ComputeIntersection(pair<double, double> s1, pair<double, double> s2, pair<double, double> i1, pair<double, double> i2) {
	double pSlope = (s2.second - s1.second)/(s2.first - s1.first);
	double pInter = s1.second - (pSlope * s1.first);

	double iSlope = (i2.second - i1.second)/(i2.first - i1.first);
	double iInter = i1.second - (iSlope * i1.first);

	pair<double, double> intersection;
	intersection.first = (pInter - iInter)/(iSlope - pSlope);
	intersection.second = (pSlope*intersection.first) + pInter;

	return intersection;
}

/**
 * Returns a vector containing a sequence of points defining
 * the intersection of two convex polygons poly1 and poly2
 * Inputs: poly1 and poly2 - sequences of points defining the
 *                           borders of convex polygons
**/
vector<pair<double, double>> GetConvexIntersection(vector<pair<double, double>>& poly1, vector<pair<double, double>>& poly2) {
	vector<pair<double, double>> isect = poly2;

	// let poly1 be the clipping polygon
	// let poly2 be the subject polygon
	
	// finding the intescting and inner points
	for (int i = 0; i < (int)poly1.size(); i++) {
		vector<pair<double, double>> inputList = isect;
		isect.clear();

		if (inputList.empty()) {
			break;
		}

		pair<double, double> prev = poly1[i];
		pair<double, double> curr;
		
		if (i == poly1.size() - 1) { // connect the last point to the first point
			curr = poly1[0];
		} else {
		 	curr = poly1[i+1];
		}

		for (int j = 0; j < (int)inputList.size(); j++) {
			pair<double, double> subPrev = inputList[j];
			pair<double, double> subCurr;
			
			if (j == inputList.size() - 1) { // connect the last point to the first point
				subCurr = inputList[0];
			} else {
			 	subCurr = inputList[j+1];
			}
			if (!isPararel(subPrev, subCurr, prev, curr)) {
				pair<double, double> intersection = ComputeIntersection(subPrev, subCurr, prev, curr); // compute intersection
				
				if (Inside(subCurr, prev, curr)) {
					if (!Inside(subPrev, prev, curr)) {
						isect.push_back(intersection);
					}
					isect.push_back(subCurr);
				} else if (Inside(subPrev, prev, curr)) {
					isect.push_back(intersection);
				}
			}
		}

		if (isect.size() < 3) {
			return {};
		}
	}


	return isect;
}
