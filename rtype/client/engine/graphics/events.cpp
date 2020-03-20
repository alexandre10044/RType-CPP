/*
** EPITECH PROJECT, 2019
** events.cpp
** File description:
** events
*/

#include <iostream>

#include "../../../../headers/client/graphics/events.hpp"
#include "../../../../headers/client/engine.hpp"

void onWindowClosed(sf::Event event, void *obj)
{
    try {
        engine *eng = (engine *)obj;
        eng->Graphics->Window.close();
        (void)event;
    } catch(...) { }
}

void onMouseClicked(sf::Event event, void *obj)
{
    try {
        engine *eng = (engine *)obj;
        int x = event.mouseButton.x * eng->Graphics->RatioWidth;
        int y = event.mouseButton.y * eng->Graphics->RatioHeight;
        
        //std::cout << std::to_string(x) << " " << std::to_string(y) << std::endl;
        if (eng->Step == MENU)
            eng->Graphics->Menu->menuClick(x, y, eng);
        else if (eng->Step == GAME)
            eng->Game->gameClick(x, y, eng);
        else if (eng->Step == SETTINGS)
            eng->Graphics->Settings->settingsClick(x, y, eng);
        else if (eng->Step == HELP)
            eng->Graphics->Help->helpClick(x, y, eng);
        else if (eng->Step == ROOMS)
            eng->Graphics->Rooms->roomsClick(x, y, eng);
    } catch(...) { }
}

void onMouseMoved(sf::Event event, void *obj)
{
    try {
        engine *eng = (engine *)obj;
        int x = event.mouseMove.x * eng->Graphics->RatioWidth;
        int y = event.mouseMove.y * eng->Graphics->RatioHeight;
        
        if (eng->Step == MENU)
            eng->Graphics->Menu->menuForecast(x, y, eng);
        else if (eng->Step == GAME)
            eng->Game->gameForecast(x, y, eng);
        else if (eng->Step == SETTINGS)
            eng->Graphics->Settings->settingsForecast(x, y, eng);
        else if (eng->Step == HELP)
            eng->Graphics->Help->helpForecast(x, y, eng);
        else if (eng->Step == ROOMS)
            eng->Graphics->Rooms->roomsForecast(x, y, eng);
    } catch(...) { }
}

void onKeyPressed(sf::Event event, void *obj)
{
    try {
        engine *eng = (engine *)obj;
        
        if (eng->Step == GAME) {
            eng->Game->Keys[(int)event.key.code] = true;
        }
    } catch(...) { }
}

void onKeyReleased(sf::Event event, void *obj)
{
    try {
        engine *eng = (engine *)obj;
        
        if (eng->Step == GAME) {
            eng->Game->Keys[(int)event.key.code] = false;
        }
    } catch(...) { }
}

void OnResized(sf::Event event, void *obj)
{
    try {
        engine *eng = (engine *)obj;

        if (eng->Step == GAME) {
            eng->Graphics->RatioWidth = 1920 / (double)event.size.width;
            eng->Graphics->RatioHeight = 1008 / (double)event.size.height;
        } else {
            eng->Graphics->RatioWidth = 900 / (double)event.size.width;
            eng->Graphics->RatioHeight = 506 / (double)event.size.height;
        }
    } catch(...) { }
}

events::events()
{
    try {
        for (int i = 0; i < INTEROP_LEN; i++)
            interop[i] = NULL;
        interop[sf::Event::Closed] = onWindowClosed;
        interop[sf::Event::MouseMoved] = onMouseMoved;
        interop[sf::Event::MouseButtonPressed] = onMouseClicked;
        interop[sf::Event::KeyPressed] = onKeyPressed;
        interop[sf::Event::KeyReleased] = onKeyReleased;
        interop[sf::Event::Resized] = OnResized;
    } catch(...) { }
}

events::~events()
{ }

void events::handleEvent(sf::Event event, void *obj)
{
    try {
        if (event.type > INTEROP_LEN)
            return;
        if (interop[event.type] != NULL)
            interop[event.type](event, obj);
    } catch(...) { }
}

void events::dispose()
{
    try {
        for (int i = 0; i < INTEROP_LEN; i++)
            interop[i] = NULL;
    } catch(...) { }
}