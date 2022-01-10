/*
 * Server.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */
/*
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
    if (!stopped) {
        stop();
    }
}*/
#include "Server.h"
#include <ostream>
#include <sys/socket.h>
#include <thread>

Server::Server(int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        throw std::runtime_error("socket failed");
    }
    // initialize struct
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Check if there is error in bind or listen
    if (bind(fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        throw std::runtime_error("bind failure");
    }
    if (listen(fd, 1) < 0) {
        throw std::runtime_error("listen failure");
    }
}

void Server::start(ClientHandler& ch) {
    // Creat new thread
    t = new thread([&ch, this](){
        // TODO: make server:stop set flag for this to exit
        struct timeval tv{};
        while (!stopServer /* running */) {
            fd_set rfds;
            FD_ZERO(&rfds);
            FD_SET(fd, &rfds);

            tv.tv_sec = 5;
            tv.tv_usec = 0;

//            cout << "server: waiting for a client" << endl;
            sockaddr_in client{};
            socklen_t clientSize = sizeof(client);

            int aClient;
            // Wait until the socket will be ready for reading, and stop it if it's necessary
            int res = select(fd + 1, &rfds, nullptr, nullptr, &tv);
            if (-1 == res) {
                throw std::runtime_error("select failure");
            } else if (FD_ISSET(fd, &rfds)) {
                aClient = accept(fd, (struct sockaddr *) &client, &clientSize);
                if (aClient < 0) { throw std::runtime_error("accept failure"); }
            } else {
//                cout << "server: select timeout" << endl;
                continue;
            }

//            cout << "server: client connected" << endl;
            // TODO: Handle in different thread - add thread to list of clients
            ch.handle(aClient);
//            cout << "server: client disconnected" << endl;
        }
    });
}

void Server::stop(){
    stopServer = true;
    t->join(); // do not delete this!
}

Server::~Server() {
    // If we haven't stopped the server, do it now
    if (!stopServer) {
        stop();
    }
}