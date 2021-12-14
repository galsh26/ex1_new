/*
 * minCircle.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include <valarray>
#include "minCircle.h"

// return the euclidean distance between two points
float distance(const Point& a, const Point& b) {
    float pow1 = (a.x - b.x) * (a.x - b.x);
    float pow2 = (a.y - b.y) * (a.y - b.y);
    float sum = pow1 + pow2;
    return sqrt(sum);
}

// check whether a point lies inside or on the boundaries of the circle
bool is_inside(const Circle& c, const Point& p) {
    return distance(c.center, p) <= c.radius;
}

// get a circle defined by 3 points
Point get_circle_center(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D),
            (bx * C - cx * B) / (2 * D)};
}

// return a unique circle that intersects three points
Circle circle_from3(const Point& A, const Point& B, const Point& C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return {I, distance(I, A)};
}

// return the smallest circle that intersects 2 points
Circle circle_from2(const Point& A, const Point& B) {
    // set the center to be the midpoint of A and B
    Point C = {(A.x + B.x) / 2, (A.y + B.y) / 2};
    // set the radius to be half the distance AB
    float r = distance(A, B) / 2;
    return Circle(C, r);
}

// check whether a circle encloses the given points
bool is_valid_circle(const Circle& c, const vector<Point>& P) {
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// find the minimum enclosing circle from the given set of points
Circle minimum_enclosing_circle(const vector<Point>& P) {
    int n = (int)P.size();
    if (n == 0) {
        return {{0, 0}, 0};
    }
    if (n == 1) {
        return {P[0], 0};
    }
    if (n == 2) {
        return circle_from2(P[0], P[1]);
    }
    Circle circle = circle_from2(P[0], P[1]);
    if (distance(P[2], circle.center) <= circle.radius) {
        return circle;
    }
    circle = circle_from2(P[0], P[2]);
    if (distance(P[1], circle.center) <= circle.radius) {
        return circle;
    }
    circle = circle_from2(P[1], P[2]);
    if (distance(P[0], circle.center) <= circle.radius) {
        return circle;
    }
    return circle_from3(P[0], P[1], P[2]);
    // go over all pair of points

}

// finds the minimal circle that contains the point
// welzl is the name of the algorithm
Circle welzl(Point** P,vector<Point> R, size_t n) {
    if(n == 0 || R.size() ==3 ) {
        return minimum_enclosing_circle(R);
    }
    int i = rand() % n;
    Point p(P[i]->x, P[i]->y);
    swap(P[i], P[n-1]);
    Circle c = welzl(P, R, n-1);
    if(distance(p,c.center) <= c.radius)
        return c;
    R.push_back(p);
    return welzl(P, R, n-1);
}

// finds the minimal circle
Circle findMinCircle(Point** points,size_t size) {
    return welzl(points,{},size);
}