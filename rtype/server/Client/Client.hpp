/*
** EPITECH PROJECT, 2019
** Client
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <mutex>
#include <queue>
#include <sys/socket.h>
#include "NetworkManager.hpp"

enum directions {
    NONE = -1,
    RIGHT,
    LEFT,
    TOP,
    BOT
};
typedef std::queue<std::pair<char*, int>> MessageQueue;
class Client {
	public:
		Client(sockaddr *);
		~Client();
        std::pair<float, float>         getPosition();
        unsigned int                    getFd();
        void                            setPosition(float x, float y);
        directions                      getDirection();
        void                            setDirection(directions d);
        void                            setClientAddress(sockaddr *sock);
        sockaddr                        *getClientAddress();
        void                            pushQueue(char*, int);
        void                            popQueue();
        MessageQueue                    getQueue();
        float                           getSpeedH();
        float                           getSpeedW();
	protected:
	private:
        std::mutex                      _client_lock;
        const float                     _speed_h = 5.0 * (1920.0 / 1008.0);
        const float                     _speed_w = 5.0;
        std::pair<float, float>         _position;
        std::string                     _address;
        unsigned int                    _port;
        unsigned int                    _fd;
        directions                      _player_direction;
        float                           _player_height;
        float                           _player_width;
        sockaddr                        *_client_addr;
        MessageQueue                    _messages;
};

#endif /* !CLIENT_HPP_ */
