/*
 * Server.cpp
 *
 * Author: Gal Schlifstein, id: 209492925
 * Author: Amit Zakai, id: 318654167
 */

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
    server.sin_port = htons(port);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    // check if there is an error
    if (bind(fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        throw std::runtime_error("bind failure");
    }
    if (listen(fd, 1) < 0) {
        throw std::runtime_error("listen failure");
    }
}

void Server::start(ClientHandler& ch) {
    // Creat new thread
    this->thr = new thread([&ch, this](){
        // we need to make server:stop set flag for this to exit
        struct timeval timeValue{};
        while (!this->serverStop) {
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(fd, &fds);

            timeValue.tv_sec = 5;
            timeValue.tv_usec = 0;

            sockaddr_in client{};
            socklen_t clientSize = sizeof(client);

            int aClient;
            // Wait until the socket will be ready for reading
            // stop it if it's necessary
            int res = select(fd + 1, &fds, nullptr, nullptr, &timeValue);
            if (res == -1) {
                throw std::runtime_error("select failure");
            } else {
                if (FD_ISSET(fd, &fds)) {
                    aClient = accept(fd, (struct sockaddr *) &client, &clientSize);
                    if (aClient < 0) {
                        throw std::runtime_error("accept failure");
                    }
                }
            }
            // we need to add thread to list of clients
            ch.handle(aClient);
        }
    });
}

void Server::stop(){
    this->serverStop = true;
    this->thr->join(); // do not delete this!
}

Server::~Server() {
    if (!this->serverStop) {
        stop();
    }
}