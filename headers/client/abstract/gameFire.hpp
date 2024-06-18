/*
** EPITECH PROJECT, 2019
** GameFire.hpp
** File description:
** gameFire
*/

#ifndef GAMEFIRE_HPP_
    #define GAMEFIRE_HPP_

    #include "../game_object.hpp"

    class GameFire: public game_object {
        public:
            int Fire;
            int Value;
            int Speed;
            int Owner;
    };


#endif /* !GAMEFIRE_HPP_ */