/*
** EPITECH PROJECT, 2019
** graphics.cpp
** File description:
** graphics
*/

#include <iostream>

#include "../../../headers/client/engine/graphics.hpp"

graphics::graphics()
{
    try {
    if (!GameFont.loadFromFile("resources/Andalus.ttf"))
        std::cout << "<Debug> Can't load font." << std::endl;
    Events = new events();
    Menu = new menu();
    Rsc = new resources();
    Settings = new settings(GameFont);
    Rooms = new rooms(GameFont);
    RatioWidth = 1.0;
    RatioHeight = 1.0;
    } catch(...) { }
}

graphics::~graphics()
{ }

void graphics::prepareWindow()
{
    try {
    Window.create(sf::VideoMode(900, 506), WINDOW_TITLE);
    std::cout << "<Debug> Window created." << std::endl; 
    } catch(...) { }
}

void graphics::clearScreen()
{
    Window.clear();
}

void graphics::displayScreen()
{
    Window.display();
}

void graphics::drawObjects(std::vector<game_object *> objs, bool sprite)
{
    for (unsigned int i = 0; i < objs.size(); i++)
        drawObject(objs[i], sprite);
}

void graphics::drawObject(game_object *obj, bool sprite)
{
    if (sprite)
        Window.draw(obj->Sp);
    else
        Window.draw(obj->Text);
}

void graphics::dispose()
{
    try {
        if (Events == NULL) {
            Events->dispose();
            Events = NULL;
        }
        if (Menu == NULL) {
            Menu->dispose();
            Menu = NULL;
        }
        if (Rsc == NULL) {
            Rsc->dispose();
            Rsc = NULL;
        }
        if (Settings == NULL) {
            Settings->dispose();
            Settings = NULL;
        }
        if (Help == NULL) {
            Help->dispose();
            Help = NULL;
        }
        if (Rooms == NULL) {
            Rooms->dispose();
            Rooms = NULL;
        }
    } catch(...) { }
}