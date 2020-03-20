/*
** EPITECH PROJECT, 2019
** Mob1
** File description:
** Mob1.hpp
*/

#ifndef Mob1_HPP_
# define Mob1_HPP_

#include"IEntity.hpp"

class Mob1 : public IEntity 
{
    public:
      ~Mob1();
        Mob1();
        void setInfo(Server *info);
        Direction getDirection();
        std::string getSkin();
        bool IsAgro();
        std::string getMunSkin();
        std::pair<int,int> getMunStat();
        int getPv();
    private:
        int _pv;
        int _dmg;
        int _speed;
        int _stamina;
        int _clientNb;
        std::vector<std::pair <int,int>> target;
        std::string _Skin;
        std::string _Mun;
};

# endif /* !Mob1_HPP_ */