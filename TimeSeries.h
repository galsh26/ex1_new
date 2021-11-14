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

//using namespace std;

class TimeSeries {
    private:
        std::map<const std::string ,std::vector<float>> mapTimeSeries;
        std::vector<float> values;
        std::vector<std::string> colNames;
        int rowSize;

    public:
        TimeSeries(const char* file_name) {
            std::ifstream myFile(file_name);
            if(!myFile.is_open()) throw std::runtime_error("can't open file");
            std::string line, column;
            float value = 0;
            std::pair<std::string, std::vector<float>> temp;
            if (myFile.good()) {
                getline(myFile, line);
                std::stringstream stream1(line);
                while (getline(stream1, column, ',')) {
                    temp.first = column;
                    this->mapTimeSeries.insert(temp);
                }
                // I think that we need to insert to colNames the info, I debbuged and it's empty
            }
            int i = 0;
            this->rowSize = colNames.size();
            while (getline(myFile, line)) {
                std::stringstream stream2(line);
                while (stream2 >> value) {
                    //this->mapTimeSeries.insert(this->colNames.at(i), temp.second.push_back(value));
                }
            }
        }
        float feature_by_time(std::string typeName, float time);
};