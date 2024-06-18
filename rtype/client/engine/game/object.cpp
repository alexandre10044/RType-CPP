/*
** EPITECH PROJECT, 2019
** gameObject.cpp
** File description:
** gameObject
*/

#include "../../../../headers/client/game.hpp"
#include "../../../../headers/client/engine.hpp"

game_object::game_object(int _id, std::string _name, int _x, int _y, int _w, int _h, int _rect, int _l)
{
    Id = _id;
    Name = _name;
    // Basic Infos
    X = _x;
    Y = _y;
    Width = _w;
    Height = _h;
    // For Image Rect
    Pos = 0;
    Rect = _rect;
    Line = _l;
    // For Entity
    Type = Unknow;
    Speed = 0;
}

game_object::~game_object()
{ }