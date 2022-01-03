/*
 * CLI.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    this->allCommands.push_back(new UploadCSVFile(dio));
    this->allCommands.push_back(new AlgoSettings(dio));
    this->allCommands.push_back(new DetectAnomaly(dio));
    this->allCommands.push_back(new DisplayResults(dio));
    this->allCommands.push_back(new UploadAndAnalize(dio));
    this->allCommands.push_back(new Exit(dio));
}

void CLI::start() {
    AllDetails allDetails;
    int choice = -1;
    while (choice != 5) {
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for (int i = 0; i < allCommands.size(); i++) {
            dio->write(i + 1);
            dio->write(".");
            dio->write(allCommands[i]->description);
            dio->write("\n");
        }
        string s = dio->read();
        choice = stoi(s);
        choice = choice - 1;
        if (choice >= 0 && choice <= 5){
            allCommands[choice]->execute(&allDetails);
        }
    }
}

CLI::~CLI() {
    for(int i = 0; i < allCommands.size(); i++){
        delete(allCommands.at(i));
    }
}