/*
 * timeseries.cpp
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

timeseries::timeseries(const char *file_name) {
    ifstream myFile(file_name);
    if(!myFile.is_open()) throw runtime_error("can't open file");
    string line, column;
    float value = 0;
    pair<string, vector<float>> temp;
    if (myFile.good()) {
        getline(myFile, line);
        stringstream stream1(line);
        while (getline(stream1, column, ',')) {
            temp.first = column;
            this->mapTimeSeries.insert(temp);
        }
    }
    int i = 0;
    this->rowSize = colNames.size();
    while (getline(myFile, line)) {
        stringstream stream2(line);
        while (stream2 >> value) {
            this->mapTimeSeries.insert(colNames.at(i), temp.second.push_back(value));
        }
    }
}

