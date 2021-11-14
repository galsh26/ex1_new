/*
 * AnomalyDetector.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include "TimeSeries.h"

//class TimeSeries{ /*...*/};
class AnomalyReport{
public:
    const std::string description;
    const long timeStep;
    AnomalyReport(std::string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual std::vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};
