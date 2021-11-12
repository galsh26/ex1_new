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

//using namespace std;

class timeseries {
    private:
        std::map<const std:: string ,std::vector<float>> mapTimeSeries;
        std::vector<float> values;
        std::vector<std::string> colNames;
        int rowSize;

    public:
        timeseries(const char* file_name);
        float feature_by_time(std::string typeName, float time);
};