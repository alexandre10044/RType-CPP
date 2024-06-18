/*
** EPITECH PROJECT, 2019
** rooms.hpp
** File description:
** rooms
*/

#ifndef rooms_HPP_
    #define rooms_HPP_

    #include "../game.hpp"

    class rooms {
        public:
            rooms(sf::Font _font);
            ~rooms();

            sf::Font GameFont;

            std::vector<game_object *> mainStep();
            std::vector<game_object *> mainTextStep();

            void roomsClick(int, int, void *);
            void roomsForecast(int, int, void *);

            void connectRoom(int, void*);
            void dispose();
            void prepareSprites(void *);
            void prepareText(void *);
            void drawRooms(void *);
    };


#endif /* !rooms_HPP_ */