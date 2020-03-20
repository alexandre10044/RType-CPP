/*
** EPITECH PROJECT, 2019
** game.hpp
** File description:
** game
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

    #include <SFML/Graphics.hpp>

    #include "abstract.hpp"
    #include "game_object.hpp"

    #define POWER_DELAY (4000)

    class game {
        public:
            game(sf::Font);
            ~game();
            std::vector<game_object *> Sprites;
            std::vector<game_object *> Texts;
            std::vector<game_object *> GUI;
            std::vector<game_object *> Entities;
            std::vector<game_object *> Monsters;
            std::vector<bool> Keys;
            bool Move = false;
            int Time;
            int Life;
            sf::Font GameFont;
        public:
            std::vector<game_object *> prepareSprites(void *, std::vector<game_object *>);
            void shootEvent(void *);
            void gameClick(int, int, void *);
            void gameForecast(int, int, void *);
            void keyEvents(void *);
            void checkForUpdate();
            void prepareText(void *);
            void prepare(void *);
            void scrollGame(void *);
            void drawGame(void *);
            void dispose();
    };

    std::vector<game_object *> mainGUIStep();
    std::vector<game_object *> mainSpritesStep();
    std::vector<game_object *> mainTextStep();

#endif /* !GAME_HPP_ */