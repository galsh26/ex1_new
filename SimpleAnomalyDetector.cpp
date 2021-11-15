#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

using namespace std;

vector<correlatedFeatures> correlations;

float getThreshold(Point** points, Line line, int size) {
    float max_thr = 0, temp;
    for (int i = 0; i < size; i++) {
        Point p = (Point) *points[i];
        temp = dev(p, line);
        if (temp > max_thr) {
            max_thr = temp;
        }
    }
    return max_thr;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    correlatedFeatures cf;
    int fea_num = ts.getNumberOfFeatures();
    int val_num = ts.getNumberOfValues();
    for (int i = 0; i < fea_num; i++) {
        int m = 0, c = -1, p;
        for (int j = i + 1; i < fea_num; j++) {
            float* fea1 = &ts.getValuesByIndex(i).at(0);
            float* fea2 = &ts.getValuesByIndex(j).at(0);
            p = abs(pearson(fea1, fea2, val_num));
            if (p > m) {
                m = p;
                c = j;
            }
            if (c != -1) {
                cf.feature1 = ts.getFeatureName(i);
                cf.feature2 = ts.getFeatureName(j);
                cf.correlation = p;
                Point **pointsArray;
                for (int k = 0; k < val_num; ++k) {
                    pointsArray[k]->x = fea1[k];
                    pointsArray[k]->y = fea2[k];
                }
                cf.lin_reg = linear_reg(pointsArray, val_num);
                cf.threshold = getThreshold(pointsArray, cf.lin_reg, val_num);
                correlations.push_back(cf);
            }
        }
    }
}

