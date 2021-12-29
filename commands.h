//
// Created by amitzakai on 12/28/21.
//


#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    // you may add additional methods here

    void getFile(string fileName){
        ofstream out(fileName);
        string raw="";
        while ((raw=read()) != "done") {
            out<<raw<<endl;
        }
        out.close();
    }
};

// you may add here helper classes

struct AllDetails {
    float threshold;
    vector<AnomalyReport> anomaly_report;
    AllDetails(){
        threshold = 0.9;
    }
};

// you may edit this class
class Command{
protected:
    DefaultIO* dio;
    const string description;
public:
    Command(DefaultIO* dio, const string description):dio(dio), description(description){}
    virtual void execute(AllDetails* allDetails)=0;
    virtual string getDes();
    virtual ~Command(){}
};

// implement here your command classes

class UploadCSVFile: public Command {
public:
    UploadCSVFile(DefaultIO* dio): Command(dio, "upload a time series csv file"){}
    virtual void execute() {
        dio->write("Please upload your local train CSV file.\n");
        dio->getFile("train.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->getFile("test.csv");
        dio->write("Upload complete.\n");
    }
    virtual string getDes(){
        return this->description;
    }
};

class AlgoSettings: public Command{
public:
    AlgoSettings(DefaultIO* dio): Command(dio, "algorithm settings"){}
    virtual void execute(AllDetails* allDetails){
        dio->write("The current correlation threshold is ");
        dio->write(allDetails->threshold);
        dio->write("\n");
        dio->write("Please choose a new threshold\n");
        float t;
        dio->read(&t);
        int mask = 0;
        while (!mask){
            if (t < 0 || t > 1){
                dio->write("please choose a value between 0 and 1.");
            } else{
                allDetails->threshold = t;
                mask = 1;
            }
        }
    }
    virtual string getDes(){
        return this->description;
    }
};

class DetectAnomaly: public Command{
public:
    DetectAnomaly(DefaultIO* dio): Command(dio, "detect anomalies"){}
    virtual void execute(AllDetails* allDetails){
        TimeSeries train("train.csv");
        TimeSeries test("test.csv");
        HybridAnomalyDetector had;
        had.setThreshold(allDetails->threshold);
        had.learnNormal(train);
        allDetails->anomaly_report = had.detect(test);

        dio->write("anomaly detection complete.\n");

    }
    virtual string getDes(){
        return this->description;
    }
};

#endif /* COMMANDS_H_ */
