/*
 * Server.h
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <netinet/in.h>
#include <thread>

#include "CLI.h"

using namespace std;

class ClientHandler{
public:
    virtual void handle(int clientID) = 0;
};

class AnomalyDetectionHandler:public ClientHandler {
public:
    void handle(int clientID) override {
        SocketIO sio = SocketIO(clientID);
        CLI clientCLI = CLI(&sio);
        clientCLI.start(); // client loop
    }
};

class Server {
    thread* thr; // run start() method in this thread
    int fd; // file description
    bool serverStop = false;

public:
    void start(ClientHandler& ch);
    void stop();
    explicit Server(int port);
    virtual ~Server();
};

#endif /* SERVER_H_ */
