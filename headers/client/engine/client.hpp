/*
** EPITECH PROJECT, 2019
** client.hpp
** File description:
** client
*/

#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #define G0(n) std::get<0>(n)
    #define G1(n) std::get<1>(n)
    #define G2(n) std::get<2>(n)

    #include "../../../rtype/network/NetworkManager.hpp"

    #define BUFFER_SIZE (4096)

    class client {
        public:
            client(void *);
            ~client();

            char buffer[BUFFER_SIZE];
            int sockfd, n;
            bool running;
            struct sockaddr_in servaddr;
            struct sockaddr_in clientaddr;
            socklen_t l;
            socklen_t m;
            pthread_t thread;
            void *tmp;
            NetworkManager *Manager;
            bool serverConnect();
            void receiveLoop();
            void dispose();
            void handleAttack(void *, void *);
            void handlePlayer(void *, void *);
            
    };

#endif /* !CLIENT_HPP_ */