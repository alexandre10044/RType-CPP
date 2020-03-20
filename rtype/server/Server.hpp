/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <sys/epoll.h>
#include <fcntl.h>
#include <thread>
#include <iomanip>
#include <mutex>
#include <stdlib.h>
#include "Log.hpp"
#include "Timer.hpp"
#include "Monster.hpp"
#include "Attack.hpp"
#include "Client.hpp"

#include "AttackMessage.hpp"
#include "MonstersMessage.hpp"
#include "PlayerMessage.hpp"
#include "ErrorMessage.hpp"


// Typedefs for socket use
typedef int                 SOCKET;
typedef struct sockaddr_in  SOCKADDR_IN;
typedef struct sockaddr     SOCKADDR;

class Server {
	public:
        // Getters setters for the mob's IA
        std::pair<float, float> getClientPosition(unsigned int client);
        // End
		Server();
		~Server();
        int     Init();
        int     Run();
        void    setPort(unsigned int port);
        int     removeClient(Client *c);
        void    updateGame();
        std::mutex  *getLock();
        NetworkManager                  *getNetworkManager();
        std::vector<Attack*>            getAttacks();
        std::vector<Monster*>           getMonsters();
        void                            setAttacks(Attack*);

	protected:
	private:

    std::mutex                      _server_lock;
    int                             _fd;
    SOCKET                          _sock;
    SOCKADDR_IN                     _server_addr;
    int                             _port;
    Timer                           _time;
    // Game
    std::vector<Client*>            _clients;
    std::vector<Monster*>           _monsters;
    std::vector<Attack*>            _attacks;
    NetworkManager                  *_manager;
    std::vector<std::thread>        _threads;
    float                           _second_elapsed;
};

#endif /* !SERVER_HPP_ */
