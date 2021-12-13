
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {

}


HybridAnomalyDetector::~HybridAnomalyDetector() {
}

void HybridAnomalyDetector::learnCF(const TimeSeries &ts, Point **ps, float p, std::string feature1, std::string feature2,
                               int val_num) {
    SimpleAnomalyDetector::learnCF(ts, ps, p, feature1, feature2, val_num);
    if (p > 0.5 && p < 0.9) {
        Circle circle = findMinCircle(ps, ts.getNumberOfValues());
        correlatedFeatures cf;
        cf.feature1 = feature1;
        cf. feature2 = feature2;
        cf.corrlation = p;
        cf.threshold = circle.radius * 1.1;
        cf.circle_x = circle.center.x;
        cf.circle_y = circle.center.y;
        this->correlations.push_back(cf);
    }
}

bool HybridAnomalyDetector::isAnomaly(float fea1, float fea2, correlatedFeatures c) {
    if (c.corrlation >= 0.9 && SimpleAnomalyDetector::isAnomaly(fea1, fea2, c)){
        return true;
    }
    if (c.corrlation > 0.5 && c.corrlation < 0.9 &&
        distance(Point(c.circle_x, c.circle_y), Point(fea1, fea2)) > c.threshold) {
        return true;
    }
    return false;
}

