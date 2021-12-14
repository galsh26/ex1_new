/*
 * minCircle.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

float distance(const Point& a, const Point& b);
bool is_inside(const Circle& c, const Point& p);
Point get_circle_center(float bx, float by, float cx, float cy);
Circle circle_from3(const Point& A, const Point& B, const Point& C);
Circle circle_from2(const Point& A, const Point& B);
bool is_valid_circle(const Circle& c, const vector<Point>& P);
Circle minimum_enclosing_circle(const vector<Point>& P);
Circle welzl(Point** P,vector<Point> R, size_t n);
Circle findMinCircle(Point** points,size_t size);

#endif /* MINCIRCLE_H_ */
