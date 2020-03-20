/*
** EPITECH PROJECT, 2019
** gameGUI.hpp
** File description:
** gameGUI
*/

#ifndef GAMEGUI_HPP_
    #define GAMEGUI_HPP_

    #include "../game_object.hpp"

    class GameGUI: public game_object {
        public:
            int Font;
            int Type;
            int Velocity;
    };

#endif /* !GAMEGUI_HPP_ */