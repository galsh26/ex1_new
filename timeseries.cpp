/*
 * TimeSeries.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include "timeseries.h"
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

TimeSeries::TimeSeries(const char *file_name) {
    ifstream myFile(file_name);
    if(!myFile.is_open()) throw std::runtime_error("Error opening file");
    string line, column;
    float value = 0;
    if (myFile.good()) {
        getline(myFile, line);
        stringstream strs(line);
        while (getline(strs, column, ',')) {
            this->tableVectors.push_back({column, vector<float>{}});
            this->featureNames.push_back(column);
        }
    }
    while (getline(myFile, line)) {
        stringstream strs(line);
        int index = 0;
        while (strs >> value) {
            this->tableVectors.at(index).second.push_back(value);
            if (strs.peek() == ',') {
                strs.ignore();
            }
            index++;
        }
    }
    this->rowSize = featureNames.size();
    this->colSize = this->tableVectors.at(1).second.size();
    myFile.close();
}

