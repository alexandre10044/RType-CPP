/*
** EPITECH PROJECT, 2019
** serverData.cpp
** File description:
** serverData
*/

#include "../../../../headers/client/data/serverData.hpp"

serverData::serverData(std::string _addr, int _port)
{
    Address = _addr;
    Port = _port;
}

serverData::~serverData()
{
    
}

void serverData::dispose()
{
    Address = "";
    Port = 0;
}