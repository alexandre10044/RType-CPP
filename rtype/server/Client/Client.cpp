/*
** EPITECH PROJECT, 2019
** Client
** File description:
** Client
*/

#include "Client.hpp"


    /*
    ** Approximative ratio of the map
    ** 1920 - 1.90476190476
    ** 1080 - 1
    ** Initiating client at mid-height and 0-width
    */
Client::Client(sockaddr* client) {
    _client_lock.lock();
    _position = std::pair<float, float>(340.0, 1008.0 / 2.0);
    _client_addr = client;
    _client_lock.unlock();
}


void         Client::popQueue() {
    _client_lock.lock();
    _messages.pop();
    _client_lock.unlock();
}

float Client::getSpeedH() {
    return (_speed_h);
}

float Client::getSpeedW() {
    return (_speed_w);
}

Client::~Client() {
}

MessageQueue    Client::getQueue() {
    std::lock_guard<std::mutex> lg(_client_lock);
    return (_messages);
}

void    Client::pushQueue(char* buffer, int size) {
    _client_lock.lock();
    _messages.push(std::pair<char*, int>(buffer, size));
    _client_lock.unlock();
}

std::pair<float, float>         Client::getPosition() {
    return (this->_position);
}


unsigned int                    Client::getFd() {
    return (this->_fd);
}

void                            Client::setPosition(float x, float y) {
    _client_lock.lock();
    this->_position = std::pair<float, float>(x, y);
    _client_lock.unlock();
}


directions                      Client::getDirection() {
    return (_player_direction);
}


void                            Client::setDirection(directions d) {
    _client_lock.lock();
    _player_direction = d;
    _client_lock.unlock();
}

void                            Client::setClientAddress(sockaddr *sock) {
    _client_lock.lock();
    _client_addr = sock;
    _client_lock.unlock();
}

sockaddr                        *Client::getClientAddress() {
    return (_client_addr);
}
