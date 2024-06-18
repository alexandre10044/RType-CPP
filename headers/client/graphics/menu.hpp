/*
** EPITECH PROJECT, 2019
** menu.hpp
** File description:
** menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <SFML/Graphics.hpp>

    #include <vector>

    enum menu_step {
        None = 0,
        Main
    };

    class menu_sprite {
        public:
            menu_sprite(int _id, std::string _name, int _x, int _y) {
                Id = _id;
                Name = _name;
                X = _x;
                Y = _y;
            }
            int Id;
            std::string Name;
            sf::Sprite Sp;
            int X, Y;
    };

    class menu {
        public:
            menu();
            ~menu();
            
            enum menu_step Step;
            std::vector<menu_sprite *> Sprites;
            std::vector<menu_sprite *> mainStep();
            void menuForecast(int, int, void *);
            void menuClick(int, int, void *);
            void prepareSprites(void *);
            void drawMenu(void *);
            void dispose();
    };

#endif /* !MENU_HPP_ */