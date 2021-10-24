// Amit Zakai 318654167
#include <iostream>
#include <cmath>

// amit add here your id :)
// Gal Schlifstein, id: 209492925

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
        var += pow(x[i] - x_mean, 2);
    }
    return var / size;
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
    return xy_cov / (sqrt(x_var) * sqrt(y_var));
}

class Line{
public:
    float a,b;
    Line():a(0),b(0){}
    Line(float a, float b):a(a),b(b){}
    float f(float x){
        return a*x+b;
    }
};
class Point{
public:
    float x,y;
    Point(float x, float y):x(x),y(y){}
    float getX() { return x;}
    float getY() { return y;}
};

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->getX();
        y[i] = points[i]->getY();
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

//---------------------------------------------------
// checks from the moodle
//---------------------------------------------------

using namespace std;
int main() {
    return 0;
}
