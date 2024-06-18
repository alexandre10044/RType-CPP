/*
** EPITECH PROJECT, 2019
** engine.hpp
** File description:
** engine
*/

#ifndef ENGINE_HPP_
    #define ENGINE_HPP_

    #include <string>

    #include "engine/client.hpp"
    #include "engine/data.hpp"
    #include "engine/graphics.hpp"
    #include "music.hpp"

    enum step_enum {
        NONE,
        MENU,
        GAME,
        HELP,
        SETTINGS,
        ROOMS,
        EXIT
    };

    class engine {
        public:
            engine(std::string host, int port);
            ~engine();

            void run();
            void abort();
            void dispose();

            bool Running;
            step_enum Step;
            client *Client;
            data *Data;
            graphics *Graphics;
            game *Game;
            music *Music;
    };


#endif /* !ENGINE_HPP_ */