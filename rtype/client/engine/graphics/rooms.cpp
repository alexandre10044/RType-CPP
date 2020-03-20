/*
** EPITECH PROJECT, 2019
** rooms.cpp
** File description:
** rooms
*/

#include <iostream>

#include "../../../../headers/client/graphics/rooms.hpp"
#include "../../../../headers/client/engine.hpp"

static std::vector<game_object *> Sprites;
static std::vector<game_object *> Texts;

rooms::rooms(sf::Font _font)
{
    GameFont = _font;
}

rooms::~rooms()
{

}

void rooms::dispose()
{
    Sprites.clear();
    Texts.clear();
}

std::vector<game_object *> rooms::mainStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "roomsPanel.png", 0, 0),
        new game_object(1, "exitButton.png", 740, 10),
    };
    return (sprites);
}


std::vector<game_object *> rooms::mainTextStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "0", 291, 157),
        new game_object(1, "0", 291, 269),
        new game_object(2, "0", 291, 389),
        new game_object(3, "0", 633, 157),
        new game_object(4, "0", 633, 269),
        new game_object(5, "0", 633, 389),
    };
    return (sprites);
}

void rooms::connectRoom(int id, void *_eng)
{
    try {
    engine *eng = (engine *)_eng;

    (void)id;
    eng->Graphics->RatioWidth = 1.0;
    eng->Graphics->RatioHeight = 1.0;
    eng->Graphics->Window.create(sf::VideoMode(1920, 1008), WINDOW_TITLE);
    eng->Game->dispose();
    eng->Step = GAME;
    } catch(...) { }
}

void rooms::roomsClick(int x, int y, void *_eng)
{
    try {
    engine *eng = (engine *)_eng;

    if (x >= 744 && x <= 885 &&
        y >= 15 && y <= 68) {
        eng->Step = MENU;
        return;
    }

    if (x >= 111 && x <= 148 &&
        y >= 128 && y <= 166) {
        connectRoom(1, eng);
    } else if (x >= 111 && x <= 148 &&
        y >= 242 && y <= 282) {
        connectRoom(2, eng);
    } else if (x >= 111 && x <= 148 &&
        y >= 361 && y <= 401) {
        connectRoom(3, eng);
    } else if (x >= 448 && x <= 488 &&
        y >= 128 && y <= 166) {
        connectRoom(4, eng);
    } else if (x >= 448 && x <= 488 &&
        y >= 242 && y <= 282) {
        connectRoom(5, eng);
    } else if (x >= 448 && x <= 488 &&
        y >= 361 && y <= 401) {
        connectRoom(6, eng);
    }
    } catch(...) { }
}

void rooms::roomsForecast(int x, int y, void *_eng)
{
    try {
    engine *eng = (engine *)_eng;

    if (Sprites.size() == 0)
        return;
    if (x >= 744 && x <= 885 &&
        y >= 15 && y <= 68) {
        if (Sprites[1]->Name.compare("exitEffectButton.png") == 0)
            return;
        Sprites[1]->Name = "exitEffectButton.png";
        Sprites[1]->Sp.setTexture(eng->Graphics->Rsc->getResource("exitEffectButton.png")->texture);
    } else {
        if (Sprites[1]->Name.compare("exitButton.png") == 0)
            return;
        Sprites[1]->Name = "exitButton.png";
        Sprites[1]->Sp.setTexture(eng->Graphics->Rsc->getResource("exitButton.png")->texture);
    }
    } catch(...) { }
}

void rooms::prepareSprites(void *_eng)
{
    try {
    engine *eng = (engine *)_eng;
    std::vector<game_object *> tmp = mainStep();

    for (unsigned int i = 0; i < tmp.size(); i++) {
        game_object *sp = tmp[i];
        entry *rsc = eng->Graphics->Rsc->getResource(sp->Name);

        if (rsc == NULL) {
            std::cout << "<Debug> Can't found resource." << std::endl;
            return;
        }
        sp->Id = Sprites.size();
        sp->Sp.setTexture(rsc->texture);
        sp->Sp.setPosition(sf::Vector2f(sp->X, sp->Y));
        Sprites.push_back(sp);
    }
    tmp.clear();
    } catch(...) { }
}

void rooms::prepareText(void *_eng)
{
    try {
    engine *eng = (engine *)_eng;
    (void)eng;
    std::vector<game_object *> tmp;

    Texts.clear();
    tmp = mainTextStep();
    for (unsigned int i = 0; i < tmp.size(); i++) {
        game_object *sp = tmp[i];

        sp->Id = Texts.size();
        sp->Text.setString(sp->Name);
        sp->Text.setFont(GameFont);
        sp->Text.setCharacterSize(17);
        sp->Text.setStyle(sf::Text::Bold);
        sp->Text.setPosition(sf::Vector2f(sp->X, sp->Y));
        Texts.push_back(sp);
    }
    } catch(...) { }
}

void rooms::drawRooms(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;

        if (Sprites.size() == 0)
            prepareSprites(eng);
        if (Texts.size() == 0)
            prepareText(eng);
        eng->Graphics->clearScreen();
        eng->Graphics->drawObjects(Sprites);
        eng->Graphics->drawObjects(Texts, false);
        eng->Graphics->displayScreen();
    } catch(...) { }
}