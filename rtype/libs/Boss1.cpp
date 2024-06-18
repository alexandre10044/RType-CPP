/*
** EPITECH PROJECT, 2019
** Boss1
** File description:
** Boss1.cpp
*/

#include"Boss1.hpp"


extern "C" IEntity *createObj(void) 
{
    return new Boss1();
}

Boss1::Boss1()
{
    _pv = 1000;
    _dmg = 25;
    _stamina = 200;
    _Skin = "";
    _Mun = "";
}

void Boss1::setInfo(Server *info)
{
    _clientNb = 1; //info->getclientNb();
    int i = 0;
    while (_clientNb > i)
        target.push_back(info->getClientPosition(i));
}

Direction Boss1::getDirection()
{
    return Direction::NONE;
}

std::string     Boss1::getSkin()
{
    return (_Skin);
}

std::pair<int,int> Boss1::getMunStat()
{
    return (std::make_pair(_dmg, _speed));
}


std::string     Boss1::getMunSkin()
{
    return (_Mun);
}

int Boss1::getPv()
{
     return (_pv);
}

bool Boss1::IsAgro()
{
    if(_ult > 15) 
    {
        _ult = 0;
        _dmg = 100;
        _Mun = "Special.jpg"
        return true;
    }
    else if (_stamina >= 100) {
        _Mun = "Normale.jpg"
        _dmg = 25;
        _stamina - 100;
        ult++;
        return true;
    }
    else if (_stamina < 100)
        _stamina += 34;
    return false;
}