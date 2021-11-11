/*
 * timeseries.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

class timeseries {
private:
    map<const string, vector<float>>;

public:
    timeseries(string file_name);
    feature_by_time(string typeName, float time);
};