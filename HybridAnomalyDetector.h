

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_


#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
    virtual bool isAnomaly(float fea1, float fea2, correlatedFeatures c);
    virtual void learnCF(const TimeSeries &ts, Point **ps, float p, std::string feature1
                         , std::string feature2,int val_num);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
