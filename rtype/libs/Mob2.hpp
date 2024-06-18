/*
** EPITECH PROJECT, 2019
** Mob2
** File description:
** Mob2.hpp
*/

#ifndef Mob2_HPP_
# define Mob2_HPP_

#include"IEntity.hpp"

class Mob2 : public IEntity 
{
    public:
      ~Mob2();
        Mob2();
        void setInfo(Server *info);
        Direction getDirection();
        std::string getSkin();
        bool IsAgro();
        std::string getMunSkin();
        std::pair<int,int> getMunStat();
        int getPv();
    private:
        int _pv;
        int _timer = 0;
        int _dmg;
        int _speed;
        int _stamina;
        int _clientNb;
        std::vector<std::pair <int,int>> target;
        std::string _Skin;
        std::string _Mun;
};

# endif /* !Mob2_HPP_ */