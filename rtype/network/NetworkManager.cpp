/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"

NetworkManager::NetworkManager()
{
    _fd = 0;
}

NetworkManager::~NetworkManager()
{
}

int    NetworkManager::init(SOCKADDR_IN *_server_addr, int _port, int *_fd)
{
    int error;
    *_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (*_fd < 0) {
        perror("Socket ");
        return (-1);
    }
    memset(_server_addr, 0, sizeof(_server_addr));
    _server_addr->sin_family = AF_INET;
    _server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    _server_addr->sin_port = htons(_port);
    error = bind(*_fd, (SOCKADDR*)_server_addr, sizeof(struct sockaddr));
    if (error < 0) {
        perror("Bind ");
        return (-1);
    }
}

void                NetworkManager::setOther(struct sockaddr *other)
{
    _other = other;
}

struct sockaddr     *NetworkManager::getOther()
{
    return (_other);
}

int     NetworkManager::getFd()
{
    return (_fd);
}

void     NetworkManager::setFd(int fd)
{
    _fd = fd;
}

int            NetworkManager::sendTo(char *buff, size_t size, struct sockaddr_in serv, socklen_t m)
{
    int         flags = 0;
    socklen_t   len = sizeof(_other);

    // J'ai fait une autre modif
    // Normalement pas besoin du serv en parametres on peu set le _other
    // TODO A voir ducoup
    //sendto(_fd, buff, sizeof(buff), flags, _other, len);
    sendto(_fd, buff, size, flags, (struct sockaddr *)&serv, m);
    // if (sendto(_fd, buff, std::string(buff).length(), flags, _other, len) != std::string(buff).length())
    //     return (-1);
    return (0);
}

std::tuple<struct sockaddr *,char*, int>     NetworkManager::receiveFrom()
{
    char        buff[BUFF_LEN] = { 0 };
    int         flags = 0;
    struct sockaddr addr;
    socklen_t   len = sizeof(addr);
    ssize_t lenReceived = recvfrom(_fd, (void*)buff, BUFF_LEN, flags, &addr, &len);
    if (lenReceived <= 0)
        return (std::tuple<struct sockaddr *,char*, int>(nullptr, (char*)"", 0));

    char    *buff2 = new char[lenReceived];
    memcpy(buff2, buff, lenReceived);
    return (std::tuple<struct sockaddr *,char*, int>(&addr, (char*)buff2, lenReceived));
}