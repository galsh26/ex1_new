/*
 * Server.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "CLI.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <csignal>
#include <sstream>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler {
public:
    virtual void handle(int clientID) = 0;
};

// you can add helper classes

class socketIO:public DefaultIO {
    int clientID;

public:
    socketIO(int clientID):clientID(clientID){}

    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);
};


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler {
public:
    virtual void handle(int clientID) {
        socketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
    // you may add data members
    int fd;
    bool stopped;
    sockaddr_in server;
    sockaddr_in client;
    thread* t;

public:
    Server(int port) throw (const char*);
    virtual ~Server();

    void start(ClientHandler& ch)throw(const char*);

    void stop();
};

#endif /* SERVER_H_ */