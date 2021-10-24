/*
 * anomaly_detection_util.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include <cmath>
#include "anomaly_detection_util.h"

// returns the mean of X
float mean(const float* x, int size) {
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / size;
}

// returns the variance of X
float var(float* x, int size) {
    float x_mean, var = 0;
    x_mean = mean(x, size);
    for (int i = 0; i < size; ++i) {
        var += powf(x[i], 2);
    }
    var = var / size;
    return (var - powf(x_mean, 2));
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    float x_mean, y_mean, var = 0;
    x_mean = mean(x, size);
    y_mean = mean(y, size);
    for (int i = 0; i < size; ++i) {
        var += (x[i] - x_mean) * (y[i] - y_mean);
    }
    return var / size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float x_var, y_var, xy_cov;
    x_var = var(x, size);
    y_var = var(y, size);
    xy_cov = cov(x, y, size);
    return xy_cov / (sqrtf(x_var) * sqrtf(y_var));
}



// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float covxy = cov(x, y, size);
    float a = covxy / var(x, size);
    float meanx = mean(x, size);
    float meany = mean(y, size);
    float b = meany - (a * meanx);
    return {a, b};
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    Line l = linear_reg(points, size);
    float expected = l.f(p.x);
    return std::abs(expected - p.y);
}

// returns the deviation between point p and the line
float dev(Point p,Line l) {
    float expected = l.f(p.x);
    return std::abs(expected - p.y);
}

using namespace std;

