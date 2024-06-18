/*
** EPITECH PROJECT, 2019
** gameText.hpp
** File description:
** gameText
*/

#ifndef GAMETEXT_HPP_
    #define GAMETEXT_HPP_

    #include "../game_object.hpp"

    class GameText: public game_object {
        public:
            int Velocity;
            int Font;
    };

#endif /* !GAMETEXT_HPP_ */