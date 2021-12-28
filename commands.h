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


// you may edit this class
class Command{
protected:
    DefaultIO* dio;
    const string description;
public:
    Command(DefaultIO* dio, const string description):dio(dio), description(description){}
    virtual void execute()=0;
    virtual string getDes();
    virtual ~Command(){}
};

// implement here your command classes

class UploadCSVFile: public Command {
public:
    UploadCSVFile(DefaultIO* dio): Command(dio, "upload a time series csv file");
    virtual void execute() {
        dio->write("Please upload your local train CSV file.\n");
        dio->getFile("");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->getFile("");
        dio->write("Upload complete.\n");
    }
    virtual string getDes(){
        return this->description;
    }
};

#endif /* COMMANDS_H_ */
