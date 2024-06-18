/*
** EPITECH PROJECT, 2019
** data.cpp
** File description:
** data
*/

#include "../../../headers/client/engine/data.hpp"

data::data(std::string _addr, int _port)
{
    ServerData = new serverData(_addr, _port);
}

data::~data()
{

}

void data::dispose()
{
    try {
    if (ServerData != NULL) {
        ServerData->dispose();
        ServerData = NULL;
    }
    } catch(...) { }
}