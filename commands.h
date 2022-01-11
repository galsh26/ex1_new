/*
 * commands.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include "timeseries.h"
#include <fstream>
#include <vector>
#include <netdb.h>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;
    virtual void write(string text) = 0;
    virtual void write(float f) = 0;
    virtual void read(float* f) = 0;
    virtual ~DefaultIO() = default;

    // you may add additional methods here

    // function to read file
    void getFile(string fileName) {
        ofstream out(fileName);
        string raw = "";
        // if "done" stop read
        while ((raw=read()) != "done") {
            out<<raw<<endl;
        }
        out.close();
    }
};


// you may add here helper classes

class SocketIO : public DefaultIO {
    int clientSocket;

public:
    explicit SocketIO(int clientSocket) : clientSocket(clientSocket) {}
    string read() override {
        string res;
        char buffer = 0;
        while (true) {
            recv(clientSocket, &buffer, sizeof(buffer), 0);
            if (buffer == '\n') {
                break;
            }
            res += buffer;
        }
        return res;
    };

    void write(string text) override { send(clientSocket, text.data(), text.size(), 0); }

    void write(float f) override {
        std::ostringstream stringStream;
        stringStream << f;
        std::string s(stringStream.str());
        send(clientSocket, s.data(), s.size(), 0);
    }

    void read(float *f) override {
        static char buffer[2]{};
        recv(clientSocket, buffer, sizeof(buffer), MSG_WAITALL);
        std::istringstream stringStream(buffer);
        stringStream >> *f;
    }
    ~SocketIO() override = default;
};

// struct to save anomalies by time step for option 5
struct TSReports {
    string description;
    int ts_start;
    int ts_end;
};

// struct to save anomalies details
struct AllDetails {
    float threshold;
    vector<AnomalyReport> anomaly_report;
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
            dio->write("Type a new threshold\n");
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
        vector<TSReports> local_an;
        vector<TSReports> user_an;

        // first get our local report

        for (int i = 0; i < allDetails->anomaly_report.size(); i++) {
            TSReports temp;
            int len = 1;
            temp.description = allDetails->anomaly_report.at(i).description;
            temp.ts_start = allDetails->anomaly_report.at(i).timeStep;
            i++;

            while (i < allDetails->anomaly_report.size() &&
                   allDetails->anomaly_report.at(i).description == temp.description &&
                   allDetails->anomaly_report.at(i).timeStep == temp.ts_start + len) {
                len++;
                i++;
            }
            temp.ts_end = temp.ts_start + len -1;
            i--;
            local_an.push_back(temp);
        }
        // get user file
        dio->write("Please upload your local anomalies file.\n");
        float sum = 0, P = 0, N, TP = 0, FP = 0;
        string line = "";
        while ((line = dio->read()) != "done") {
            stringstream ss(line);
            int start, end;
            ss >> start;
            if (ss.peek() == ',') ss.ignore();
            ss >> end;
            sum += end - start + 1;
            P++;
            TSReports temp;
            temp.description = "";
            temp.ts_start = start;
            temp.ts_end = end;
            user_an.push_back(temp);
        }
        dio->write("Upload complete.\n");

        N = allDetails->raws - sum;

        for (TSReports &l_tsr : local_an) {
            for (TSReports &u_tsr : user_an) {
                if (u_tsr.ts_start <= l_tsr.ts_end && u_tsr.ts_end >= l_tsr.ts_start) {
                    TP++;
                }
            }
        }

        FP = local_an.size() - TP;
        float tpr=(int)(1000.0 * (TP / P)) / 1000.0f;
        float fpr=(int)(1000.0 * (FP / N)) / 1000.0f;
        dio->write("True Positive Rate: ");
        dio->write(tpr);
        dio->write("\n");
        dio->write("False Positive Rate: ");
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
