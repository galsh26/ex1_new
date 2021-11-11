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
        map<string,vector<float>> mapTimeSeries;
        vector<string> columns;
        int rowSize;

    public:
        timeseries(const char* file_name) {
            // we need to write here the method implementation
        }
        feature_by_time(string typeName, float time) {
            // we need to write here the method implementation
        }
};