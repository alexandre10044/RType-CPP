/*
** EPITECH PROJECT, 2019
** engine.cpp
** File description:
** engine
*/

#include <iostream>

#include "../../headers/client/engine.hpp"

engine::engine(std::string _addr, int _port)
{
    Data = new data(_addr, _port);
    Graphics = new graphics();
    Music = new music();
    Client = new client(this);
    Running = false;
    Game = new game(Graphics->GameFont);
    Step = NONE;
}

engine::~engine()
{ }

void engine::run()
{
    try {
        if (Running || !Client->serverConnect())
            return;
        sf::Clock clock;
        Running = true;
        Graphics->Rsc->loadResources();
        Graphics->prepareWindow();
        Graphics->Window.setFramerateLimit(60);
        Music->Play();
        Step = MENU;

        std::cout << "<Debug> Engine started, waiting for user event." << std::endl;
        while (Running && Graphics->Window.isOpen()) {
            if (clock.getElapsedTime().asMilliseconds() <= 1000 / Graphics->Settings->Fps)
                continue;
            sf::Event event;
            while (Graphics->Window.pollEvent(event))
                Graphics->Events->handleEvent(event, this);
            if (Step == MENU)
                Graphics->Menu->drawMenu(this);
            else if (Step == GAME)
                Game->drawGame(this);
            else if (Step == SETTINGS)
                Graphics->Settings->drawSettings(this);
            else if (Step == HELP)
                Graphics->Help->drawHelp(this);
            else if (Step == ROOMS)
                Graphics->Rooms->drawRooms(this);
            else
                return;
            clock.restart();
        }
    } catch(...) { }
}

void engine::abort()
{
    if (!Running)
        return;
    try {
        Running = false;
        if (Music != NULL)
            Music->Stop();
        std::cout << "<Debug> Abort." << std::endl;
    } catch(...) { }
}

void engine::dispose()
{
    try {
        if (Data != NULL) {
            Data->dispose();
            Data = NULL;
        }
        if (Graphics != NULL) {
            Graphics->dispose();
            Graphics = NULL;
        }
        if (Client != NULL) {
            Client->dispose();
            Client = NULL;
        }
        if (Game != NULL) {
            Game->dispose();
            Game = NULL;
        }
    } catch(...) { }
}