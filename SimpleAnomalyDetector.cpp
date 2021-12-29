#include "SimpleAnomalyDetector.h"
//#include "anomaly_detection_util.h"

/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

using namespace std;

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->threshold = 0.9;
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() noexcept {}

Point** getPointsArray(const float* a,const float* b, int size) {
    Point** p = new Point*[size];
    for(int i = 0; i < size; i++) {
        p[i] = new Point(a[i],b[i]);
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


void SimpleAnomalyDetector::learnCF(const TimeSeries &ts, Point **ps, float p, std::string feature1,
                                    std::string feature2, int val_num) {
    if(p > this->threshold) {
        correlatedFeatures cf;
        cf.feature1 = feature1;
        cf.feature2 = feature2;
        cf.corrlation = p;
        cf.lin_reg = linear_reg(ps, val_num);
        cf.threshold = getThreshold(ps, cf.lin_reg, val_num).first * 1.1;
        // save in corrlation
        this->correlations.push_back(cf);
    }
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    // temp structure for correlated feature
    int fea_num = ts.getNumberOfFeatures();
    int val_num = ts.getNumberOfValues();
    for (int i = 0; i < fea_num; i++) {
        float m = 0, c = -1, p;
        for (int j = i + 1; j < fea_num; j++) {
            // casting vectors to pointers array
            vector<float> temp1 = ts.getValuesByIndex(i);
            vector<float> temp2 = ts.getValuesByIndex(j);
            float* fea1 = &temp1[0];
            float* fea2 = &temp2[0];
            // calculate corrlation
            p = pearson(fea1, fea2, val_num);
            // abs
            if (p < 0) {
                p = p * (-1);
            }
            // if correlated switch
            if (p > m) {
                m = p;
                c = j;
            }
            string f_name1 = ts.getFeatureName(i);
            string f_name2 = ts.getFeatureName(j);
            Point **pointsArray = getPointsArray(fea1, fea2, val_num);
            if (c != -1) {
                learnCF(ts, pointsArray,p, f_name1, f_name2,val_num);
            }
        }
    }
}

bool SimpleAnomalyDetector::isAnomaly(float fea1, float fea2, correlatedFeatures c) {
    return (c.threshold < abs(fea2 - c.lin_reg.f(fea1)));
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> anomaly_reports;
    correlatedFeatures temp;
    int numOfCorr = this->correlations.size();
    for(int i = 0; i < numOfCorr; i++) {
        //temp.feature1 = this->correlations.at(i).feature1;
        //temp.feature2 = this->correlations.at(i).feature2;
        temp = this->correlations.at(i);
        //int size = ts.getNumberOfValues();
        vector<float> temp1 = ts.getValuesByName(temp.feature1);
        vector<float> temp2 = ts.getValuesByName(temp.feature2);
        /*
        float* arr1 = &temp1[0];
        float* arr2 = &temp2[0];
        Point **pointsArray = getPointsArray(arr1, arr2, size);
        temp.lin_reg = linear_reg(pointsArray, size);
        pair<float, int> pr = getThreshold(pointsArray, temp.lin_reg, size);
        temp.threshold = pr.first;
        if (temp.threshold > this->correlations.at(i).threshold) {
            string des = temp.feature1 + '-' + temp.feature2;
            int row_ano = pr.second;
            anomaly_reports.push_back(AnomalyReport(des, row_ano));
        }
        */
        for (int j = 0; j < temp1.size(); j++) {
            if (isAnomaly(temp1[j], temp2[j], temp)){
                string des = temp.feature1 + '-' + temp.feature2;
                anomaly_reports.push_back(AnomalyReport(des, j+1));
            }
        }
    }
    return anomaly_reports;
}

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return this->correlations;
}

