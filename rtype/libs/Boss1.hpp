/*
** EPITECH PROJECT, 2019
** Boss1
** File description:
** Boss1.hpp
*/

#ifndef Boss1_HPP_
# define Boss1_HPP_

#include"IEntity.hpp"

class Boss1 : public IEntity 
{
    public:
      ~Boss1();
        Boss1();
        void setInfo(Server *info);
        Direction getDirection();
        std::string getSkin();
        bool IsAgro();
        std::string getMunSkin();
        std::pair<int,int> getMunStat();
        int getPv();
    private:
        int _pv;
        int _ult;
        int _dmg;
        int _speed;
        int _stamina;
        int _clientNb;
        std::vector<std::pair <int,int>> target;
        std::string _Skin;
        std::string _Mun;
};

# endif /* !Boss1_HPP_ */