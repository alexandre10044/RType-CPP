/*
** EPITECH PROJECT, 2019
** graphics.hpp
** File description:
** graphics
*/

#ifndef GRAPHICS_HPP_
    #define GRAPHICS_HPP_

    #include <SFML/Graphics.hpp>

    #include "../game.hpp"
    #include "../IGraphic.hpp"
    #include "../graphics/events.hpp"
    #include "../graphics/menu.hpp"
    #include "../graphics/help.hpp"
    #include "../graphics/settings.hpp"
    #include "../graphics/resources.hpp"
    #include "../graphics/rooms.hpp"

    #define WINDOW_TITLE ("Rtype")

    class graphics : public IGraphic {
        public:
            graphics();
            ~graphics();

            void dispose();
            void prepareWindow();
            void clearScreen();
            void displayScreen();
            void drawObject(game_object *, bool = true);
            void drawObjects(std::vector<game_object *>, bool = true);

            double RatioWidth;
            double RatioHeight;
            events *Events;
            menu *Menu;
            settings *Settings;
            rooms *Rooms;
            help *Help;
            resources *Rsc;
            sf::RenderWindow Window;
            sf::Font GameFont;
    };

#endif /* !GRAPHICS_HPP_ */