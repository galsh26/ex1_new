/*
 * Server.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

#include "Server.h"
#include <unistd.h>
#include <csignal>

string socketIO::read() {
    char c = 0;
    string s;
    while(c != '\n') {
        recv(clientID,&c,sizeof(char),0);
        s += c;
    }
    return s;
}

void socketIO::write(string text) {
    const char* txt = text.c_str();
    send(clientID,txt,strlen(txt),0);
}

void socketIO::write(float f) {
    ostringstream stringStream;
    stringStream << f;
    string s(stringStream.str());
    write(s);
}

void socketIO::read(float* f) {}

Server::Server(int port) throw (const char*) {
    this->stopped = false;
    this->fd = socket(AF_INET,SOCK_STREAM,0);
    if(this->fd < 0) {
        throw "socket failed";
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if(bind(this->fd,(struct sockaddr*) &this->server, sizeof(this->server)) < 0) {
        throw "bind failure";
    }

    if(listen(this->fd, 3) < 0) {
        throw "listen failure";
    }
}

void sigHandler(int signum) {}

void Server::start(ClientHandler& ch)throw(const char*) {
    this->t = new thread([&ch, this](){
        signal(SIGALRM,sigHandler);
        while(!(this->stopped)) {
            socklen_t clientSize=sizeof(this->client);
            alarm(1);
            int acceptClient = accept(this->fd,(struct sockaddr*) &(this->client),&clientSize);
            if(acceptClient > 0) {
                ch.handle(acceptClient);
                close(acceptClient);
            }
            alarm(0);
        }
        close(this->fd);
    });
}

void Server::stop() {
    this->stopped = true;
    t->join();
}

Server::~Server() {
    // TODO Auto-generated destructor stub
}