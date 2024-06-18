/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <tuple>
#include <iostream>

#define BUFF_LEN 4096

typedef struct sockaddr_in  SOCKADDR_IN;
typedef struct sockaddr     SOCKADDR;

enum    MessagesId {
    ATTACK = 0,
    MONSTER,
    PLAYER
};

class NetworkManager {
	public:
		NetworkManager();
		~NetworkManager();
        void            setOther(struct sockaddr *other);
        int            init(SOCKADDR_IN *server, int _port, int *_fd);
        struct sockaddr *getOther();
        int             getFd();
        void            setFd(int fd);
        int                                         sendTo(char buff[BUFF_LEN], size_t n, struct sockaddr_in serv, socklen_t m);
        std::tuple<struct sockaddr *,char*, int>    receiveFrom();
	protected:
	private:
        struct sockaddr *_other;
        int             _fd;

};

#endif /* !NETWORKMANAGER_HPP_ */
