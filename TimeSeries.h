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
        std::vector<std::string> featureNames;
        int rowSize;

    public:
        TimeSeries(const char* file_name);
        float feature_by_time(std::string typeName, float time);
        std::vector<float> getValuesVector(std::string feature){
            for (int i = 0; i < this->rowSize; i++) {
                if (this->featureNames.at(i).compare(feature)) {
                    return this->tableVectors.at(i).second;
                }
            }
        }
        std::vector<std::string> getFeatureNames() {
            return this->featureNames;
        }

};
