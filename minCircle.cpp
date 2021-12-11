/*
 * anomaly_detection_util.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include <cmath>
#include <vector>
#include "minCircle.h"

using namespace std;

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
Circle circle_from(const Point& A, const Point& B, const Point& C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return {I, distance(I, A)};
}

// return the smallest circle that intersects 2 points
Circle circle_from(const Point& A, const Point& B) {
    // set the center to be the midpoint of A and B
    Point C = {(A.x + B.x) / 2, (A.y + B.y) / 2};
    // set the radius to be half the distance AB
    return {C, distance(A, B) / 2};
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
    Circle circle = {{0, 0}, INFINITY};
    // go over all pair of points
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // get the smallest circle that intersects P[i] and P[j]
            Circle tmp = circle_from(P[i], P[j]);
            // update circle if tmp encloses all points and has a smaller radius
            if (tmp.radius < circle.radius && is_valid_circle(tmp, P))
                circle = tmp;
        }
    }

    // Go over all triples of points
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                // get the circle that intersects P[i], P[j], P[k]
                Circle tmp = circle_from(P[i], P[j], P[k]);
                // update circle if tmp encloses all points and has smaller radius
                if (tmp.radius < circle.radius && is_valid_circle(tmp, P))
                    circle = tmp;
            }
        }
    }
    return circle;
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