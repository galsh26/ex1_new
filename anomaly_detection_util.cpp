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
    float x_mean, var;
    x_mean = mean(x, size);
    for (int i = 0; i < size; ++i) {
        var += pow(x[i] - x_mean, 2);
    }
    return var / size;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    float x_mean, y_mean, var;
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

bool wrong(float val, float expected) {
    return val < expected - 0.001 || val > expected + 0.001;
}
int main() {
    const int N=10;
    float x[]={1,2,3,4,5,6,7,8,9,10};
    float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};

    Point* ps[N];
    for(int i=0;i<N;i++)
        ps[i]=new Point(x[i],y[i]);

    Line l=linear_reg(ps,N);
    Point p(4,8);

    float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
    float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};


    for(int i=0;i<7;i++)
        if(wrong(v[i],e[i]))
            cout<<"error for check "<<i<<" (-14)"<<endl;


    for(int i=0;i<N;i++)
        delete ps[i];

    cout<<"done"<<endl;
    return 0;
}