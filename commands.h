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
    virtual ~DefaultIO() = default;

    // you may add additional methods here

    // function to read file
    void getFile(string fileName){
        ofstream out(fileName);
        string raw="";
        // if "done" stop read
        while ((raw=read()) != "done") {
            out<<raw<<endl;
        }
        out.close();
    }
};


// you may add here helper classes



// struct to save anomalies by time step for option 5
struct TSReports {
    string description;
    int ts_start;
    int ts_end;
    bool tp;
    TSReports(){
        tp = false;
    }
};

// struct to save anomalies details
struct AllDetails {
    float threshold;
    vector<AnomalyReport> anomaly_report;
    vector<TSReports> ts_report;
    int raws;
    AllDetails(){
        threshold = 0.9;
        raws = 0;
    }
};



// you may edit this class
class Command{
protected:
    DefaultIO* dio;
    //const string description;
public:
    const string description;
    Command(DefaultIO* dio, const string description):dio(dio), description(description){}
    virtual void execute(AllDetails* allDetails)=0;
    virtual string getDes()=0;
    virtual ~Command(){}
};

// implement here your command classes


class UploadCSVFile: public Command {
public:
    UploadCSVFile(DefaultIO* dio): Command(dio, "upload a time series csv file"){}
    virtual void execute(AllDetails* allDetails) {
        // get training file
        dio->write("Please upload your local train CSV file.\n");
        dio->getFile("train.csv");
        dio->write("Upload complete.\n");
        // test file
        dio->write("Please upload your local test CSV file.\n");
        dio->getFile("test.csv");
        dio->write("Upload complete.\n");
    }
    string getDes(){
        return this->description;
    }
};


class AlgoSettings: public Command{
public:
    AlgoSettings(DefaultIO* dio): Command(dio, "algorithm settings"){}
    virtual void execute(AllDetails* allDetails){
        bool mask = false;
        while (!mask) {
            dio->write("The current correlation threshold is ");
            dio->write(allDetails->threshold);
            dio->write("\n");
            dio->write("Please choose a new threshold\n");
            float thre;
            dio->read(&thre);
            if(thre <= 0 || thre >= 1){
                dio->write("please choose a value between 0 and 1.\n");
            }
            else{
                allDetails->threshold=thre;
                mask = true;
            }
        }
    }
    // get command description
    
    string getDes(){
        return this->description;
    }
};

class DetectAnomaly: public Command{
public:
    DetectAnomaly(DefaultIO* dio): Command(dio, "detect anomalies"){}
    virtual void execute(AllDetails* allDetails){
        // detect anomalies by hybrid
        TimeSeries train("train.csv");
        TimeSeries test("test.csv");
        HybridAnomalyDetector had;
        had.setThreshold(allDetails->threshold);
        had.learnNormal(train);
        allDetails->anomaly_report = had.detect(test);
        allDetails->raws = test.getNumberOfValues();

        // save all result in the anomaly by time step report
        TSReports tsr;
        tsr.ts_start = 0;
        tsr.ts_end = 0;
        tsr.description = " ";
        for (int i = 0; i < allDetails->anomaly_report.size(); i++) {
            AnomalyReport temp = allDetails->anomaly_report.at(i);
            if (tsr.description == temp.description && tsr.ts_end + 1 == temp.timeStep){
                tsr.ts_end++;
            } else {
                allDetails->ts_report.push_back(tsr);
                tsr.ts_start = temp.timeStep;
                tsr.ts_end = tsr.ts_start;
                tsr.description = temp.description;
            }
        }
        allDetails->ts_report.push_back(tsr);
        allDetails->ts_report.erase(allDetails->ts_report.begin());

        dio->write("anomaly detection complete.\n");

    }
    string getDes(){
        return this->description;
    }
};

class DisplayResults: public Command{
public:
    DisplayResults(DefaultIO* dio): Command(dio, "display results"){}
    virtual void execute(AllDetails* allDetails){
        int size = allDetails->anomaly_report.size();
        for (int i = 0; i < size; i++) {
            dio->write(allDetails->anomaly_report.at(i).timeStep);
            dio->write("\t ");
            dio->write(allDetails->anomaly_report.at(i).description);
            dio->write("\n");
        }
        dio->write("Done.\n");
    }

    string getDes(){
        return this->description;
    }
};

class UploadAndAnalize: public Command{
public:
    UploadAndAnalize(DefaultIO* dio): Command(dio, "upload anomalies and analyze results"){}

    virtual void execute(AllDetails* allDetails) {
        dio->write("Please upload your local anomalies file.\n");
        string raw ="";
        int comma;
        float tp = 0, fp = 0, p = 0, sum = 0;
        while ((raw = dio->read()) != "done"){
            for (int i = 0; i < raw.length(); i++) {
                if (raw[i] == ',') {
                    comma = i;
                    break;
                }
            }
            int start = stoi(raw.substr(0, comma));
            int end = stoi(raw.substr(comma + 1, raw.length()));
            bool check = false;
            for (int i = 0; i < allDetails->ts_report.size(); i++) {
                TSReports tsr = allDetails->ts_report.at(i);
                if (end >= tsr.ts_start && tsr.ts_end >= start) {
                    allDetails->ts_report.at(i).tp = true;
                    check = true;
                    break;
                }
            }
            if (check) {
                tp++;
            }
            sum = sum + (end + 1 - start);
            p++;
        }
        dio->write("Upload complete.\n");
        for (int i = 0; i < allDetails->ts_report.size(); i++) {
            if (!allDetails->ts_report.at(i).tp) {
                fp++;
            }
        }
        // define raws without anomaly
        float n = allDetails->raws - sum;
        // define true positive
        float t = tp / p;
        // define false positive
        float f = fp / n;
        // print only 3 digits maximum
        float N=allDetails->raws - sum;
        float tpr=((int)(1000.0*tp/p))/1000.0f;
        float fpr=((int)(1000.0*fp/N))/1000.0f;
        dio->write("True Positive Rate: ");
        dio->write(tpr);
        dio->write("\nFalse Positive Rate: ");
        dio->write(fpr);
        dio->write("\n");

    }


    string getDes(){
        return this->description;
    }
};

class Exit: public Command{
public:
    Exit(DefaultIO* dio): Command(dio, "exit"){}
    virtual void execute(AllDetails* allDetails){};
    string getDes(){
        return this->description;
    }
};


#endif /* COMMANDS_H_ */
