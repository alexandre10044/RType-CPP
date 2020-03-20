/*
** EPITECH PROJECT, 2019
** gameMonster.hpp
** File description:
** gameMonster
*/

#ifndef GAMEMONSTER_HPP_
    #define GAMEMONSTER_HPP_

    #include "../game_object.hpp"

    class GameMonster: public game_object {
        public:
            int Type;
            int Speed;
            int Damage;
    };


#endif /* !GAMEMONSTER_HPP_ */