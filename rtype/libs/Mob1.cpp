/*
** EPITECH PROJECT, 2019
** Mob1
** File description:
** Mob1.cpp
*/

#include"Mob1.hpp"


extern "C" IEntity *createObj(void) 
{
    return new Mob1();
}

Mob1::Mob1()
{
    _pv = 100;
    _dmg = 25;
    _stamina = 100;
    _Skin = "";
    _Mun = "";
}

void Mob1::setInfo(Server *info)
{
    _clientNb = 1; //info->getclientNb();
    int i = 0;
    while (_clientNb > i)
        target.push_back(info->getClientPosition(i));
}

Direction Mob1::getDirection()
{
    return Direction::NONE;
}

std::string     Mob1::getSkin()
{
    return (_Skin);
}

std::pair<int,int> Mob1::getMunStat()
{
    return (std::make_pair(_dmg, _speed));
}


std::string     Mob1::getMunSkin()
{
    return (_Mun);
}

int Mob1::getPv()
{
     return (_pv);
}

bool Mob1::IsAgro()
{
    if (_stamina == 100) {
        _stamina - 100;
        return true;
    }
    else 
        _stamina += 25;
    return false;
}

