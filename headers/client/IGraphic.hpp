/*
** EPITECH PROJECT, 2019
** IGraphic.hpp
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
    #define IGRAPHIC_HPP_

    #include <vector>

    #include "game_object.hpp"

    class IGraphic {
        public:
            void dispose();
            void prepareWindow();
            void clearScreen();
            void displayScreen();
            void drawObject(game_object *, bool = true);
            void drawObjects(std::vector<game_object *>, bool = true);
    };

#endif /* !IGRAPHIC_HPP_ */