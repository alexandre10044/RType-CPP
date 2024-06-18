/*
** EPITECH PROJECT, 2019
** settings.hpp
** File description:
** settings
*/

#ifndef SETTINGS_HPP_
    #define SETTINGS_HPP_

    #include "../game.hpp"

    class settings {
        public:
            settings(sf::Font);
            ~settings();

            int Fps;
            int Sound;
            int Quality;
            sf::Font GameFont;
            std::vector<game_object *> mainStep();
            std::vector<game_object *> mainTextStep();

            void settingsClick(int, int, void *);
            void settingsForecast(int, int, void *);

            void dispose();
            void checkForUpdate();
            void prepareSprites(void *);
            void prepareText(void *);
            void drawSettings(void *);
    };


#endif /* !SETTINGS_HPP_ */