/*
** EPITECH PROJECT, 2019
** help.hpp
** File description:
** help
*/

#ifndef HELP_HPP_
    #define HELP_HPP_

    #include "../game.hpp"

    class help {
        public:
            help();
            ~help();

            std::vector<game_object *> mainStep();

            void helpClick(int, int, void *);
            void helpForecast(int, int, void *);

            void dispose();
            void prepareSprites(void *);
            void drawHelp(void *);
    };


#endif /* !HELP_HPP_ */