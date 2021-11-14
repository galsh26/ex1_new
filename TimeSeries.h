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
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

class TimeSeries {
    private:
        std::vector<std::pair<std::string, std::vector<float>>> tableVectors;
        std::vector<float> values;
        std::vector<std::string> colNames;
        int rowSize;

    public:
        TimeSeries(const char* file_name);
        float feature_by_time(std::string typeName, float time);
};
