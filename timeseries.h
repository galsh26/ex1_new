/*
 * TimeSeries.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

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
        int colSize;

    public:
        TimeSeries(const char* file_name);

        float get_feature_by_time(std::string typeName, float time) const;

        std::vector<float> getValuesByName(std::string feature) const{
            for (int i = 0; i < this->rowSize; i++) {
                if (this->featureNames.at(i).compare(feature)) {
                    return this->tableVectors.at(i).second;
                }
            }
        }

        std::vector<float> getValuesByIndex(int n) const{
            return this->tableVectors.at(n).second;
        }

        std::vector<std::string> getFeatureVector() const{
            return this->featureNames;
        }

        std::string getFeatureName(int n) const{
            return this->featureNames.at(n);
        }

        int getNumberOfFeatures() const {
            return this->rowSize;
        }
        int getNumberOfValues() const {
            return this->colSize;
        }
};

#endif /* TIMESERIES_H_ */
