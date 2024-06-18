/*
** EPITECH PROJECT, 2019
** Mob2
** File description:
** Mob2.cpp
*/

#include"Mob2.hpp"


extern "C" IEntity *createObj(void) 
{
    return new Mob2();
}

Mob2::Mob2()
{
    _pv = 250;
    _dmg = 25;
    _stamina = 100;
    _Skin = "";
    _Mun = "";
}

void Mob2::setInfo(Server *info)
{
    _clientNb = 1; //info->getclientNb();
    int i = 0;
    while (_clientNb > i)
        target.push_back(info->getClientPosition(i));
}

Direction Mob2::getDirection()
{
    if (_timer != 2){
        _timer = _timer - 1;
        return Direction::BOT;

    }
    else {
        _timer++;
       return Direction::TOP; 
    }
    return Direction::NONE;
}

std::string     Mob2::getSkin()
{
    return (_Skin);
}

std::pair<int,int> Mob2::getMunStat()
{
    return (std::make_pair(_dmg, _speed));
}


std::string     Mob2::getMunSkin()
{
    return (_Mun);
}

int Mob2::getPv()
{
     return (_pv);
}

bool Mob2::IsAgro()
{
    if (_stamina > 75) {
        _stamina - 75;
        return true;
    }
    else 
        _stamina += 25;
    return false;
}

