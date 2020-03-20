/*
** EPITECH PROJECT, 2019
** IEntity
** File description:
** IEntity.hpp
*/

#ifndef IENTITY_HPP_
# define IENTITY_HPP_
#include "../server/Server.hpp"
#include <iostream>
#include <string>
#include<utility>
#include <vector>

enum Direction {
    TOP,
    BOT,
    MID,
    NONE
};

class IEntity
{
    public:
        virtual ~IEntity() = default;
        virtual void setInfo(Server *);
        virtual  Direction getDirection();
        virtual std::string getSkin();
        virtual bool IsAgro();
        virtual std::string getMunSkin()
        virtual std::pair<int,int> getMunStat();
        virtual int getPv();
};


# endif /* !IENTITY_HPP_ */