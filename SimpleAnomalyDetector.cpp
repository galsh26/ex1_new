#include "SimpleAnomalyDetector.h"
//#include "anomaly_detection_util.h"

/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

using namespace std;

Point** getPointsArray(float* a, float* b, int size) {
    Point **p;
    for (int i = 0; i < size; ++i) {
        p[i]->x = a[i];
        p[i]->y = b[i];
    }
    return p;
}
// calculate threshold for line of features
pair<float, int> getThreshold(Point** points, Line line, int size) {
    pair<float, int> pr;
    float max_thr = 0, temp;
    int row, counter = 1;
    for (int i = 0; i < size; i++) {
        Point p = (Point) *points[i];
        temp = dev(p, line);
        if (temp > max_thr) {
            max_thr = temp;
            row = counter;
        }
        counter++;
    }
    pr.first = max_thr;
    pr.second = row;
    return pr;
}

void SimpleAnomalyDetector::learnNormal(const timeseries &ts) {
    // temp structure for correlated features
    correlatedFeatures cf;
    int fea_num = ts.getNumberOfFeatures();
    int val_num = ts.getNumberOfValues();
    for (int i = 0; i < fea_num; i++) {
        int m = 0, c = -1, p;
        for (int j = i + 1; i < fea_num; j++) {
            // casting vectors to pointers array
            float* fea1 = &ts.getValuesByIndex(i).at(0);
            float* fea2 = &ts.getValuesByIndex(j).at(0);
            // calculate correlation
            p = abs(pearson(fea1, fea2, val_num));
            // if correlated switch
            if (p > m) {
                m = p;
                c = j;
            }
            // save in temp structure
            if (c != -1) {
                cf.feature1 = ts.getFeatureName(i);
                cf.feature2 = ts.getFeatureName(j);
                cf.correlation = p;
                Point **pointsArray = getPointsArray(fea1, fea2, val_num);
                cf.lin_reg = linear_reg(pointsArray, val_num);
                cf.threshold = getThreshold(pointsArray, cf.lin_reg, val_num).first * 1.1;
                // save in correlation
                this->correlations.push_back(cf);
            }
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const timeseries &ts) {
    vector<AnomalyReport> anomaly_reports;
    correlatedFeatures temp;
    for(correlatedFeatures i : this->correlations) {
        temp.feature1 = i.feature1;
        temp.feature2 = i.feature2;
        int size = ts.getNumberOfValues();
        float* arr1 = &ts.getValuesByName(temp.feature1).at(0);
        float* arr2 = &ts.getValuesByName(temp.feature2).at(0);
        //temp.correlation = abs(pearson(arr1, arr2, size));
        Point **pointsArray = getPointsArray(arr1, arr2, size);
        temp.lin_reg = linear_reg(pointsArray, size);
        pair<float, int> pr = getThreshold(pointsArray, temp.lin_reg, size);
        temp.threshold = pr.first;
        if (temp.threshold > i.threshold) {
            string des = temp.feature1 + '-' + temp.feature2;
            int row_ano = pr.second;
            anomaly_reports.push_back(AnomalyReport(des, row_ano));
        }
    }
    return anomaly_reports;
}

