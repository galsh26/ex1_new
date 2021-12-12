/*
 * SimpleAnomalyDetector.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include <algorithm>
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"

struct correlatedFeatures{
    std::string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    float circle_x;
    float circle_y;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
    std::vector<correlatedFeatures> correlations;

public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual void learnNormal(const TimeSeries& ts);
    virtual std::vector<AnomalyReport> detect(const TimeSeries& ts);
    virtual std::vector<correlatedFeatures> getNormalModel();

protected:
    virtual void learnCF(const TimeSeries &ts, Point **ps, float p, std::string feature1,
                         std::string feature2, int val_num);
    virtual bool isAnomaly(float fea1, float fea2, correlatedFeatures c);
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */