#include <string>
#include <vector>
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"

/*
 * SimpleAnomalyDetector.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

struct correlatedFeatures{

    std::string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
private:
    std::vector<correlatedFeatures> correlations;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const timeseries& ts);
    virtual std::vector<AnomalyReport> detect(const timeseries& ts);
    std::vector<correlatedFeatures> getNormalModel();
};