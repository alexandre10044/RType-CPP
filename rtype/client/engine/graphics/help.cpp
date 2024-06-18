/*
** EPITECH PROJECT, 2019
** help.cpp
** File description:
** help
*/

#include <iostream>

#include "../../../../headers/client/graphics/help.hpp"
#include "../../../../headers/client/engine.hpp"

static std::vector<game_object *> Sprites;
static std::vector<game_object *> Texts;

help::help()
{
    Sprites.clear();
}

help::~help()
{

}

void help::dispose()
{
    Sprites.clear();
    Texts.clear();
}

std::vector<game_object *> help::mainStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "helpPanel.png", 0, 0),
        new game_object(1, "exitButton.png", 740, 10),
    };
    return (sprites);
}


void help::helpClick(int x, int y, void *_eng)
{
    try {
    engine *eng = (engine *)_eng;

    if (x >= 744 && x <= 885 &&
        y >= 15 && y <= 68) {
        eng->Step = MENU;
    }
    } catch(...) { }
}

void help::helpForecast(int x, int y, void *_eng)
{
    static const std::string exitEffect = "exitEffectButton.png";
    static const std::string exit = "exitButton.png";
    int index = 1;

    try {
        engine *eng = (engine *)_eng;

        if (!Sprites.size())
            return;
        if (x >= 744 && x <= 885 &&
            y >= 15 && y <= 68) {
            if (!Sprites[index]->Name.compare(exitEffect))
                return;
            Sprites[index]->Name = exitEffect;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(exitEffect)->texture);
        } else {
            if (!Sprites[index]->Name.compare(exit))
                return;
            Sprites[index]->Name = exit;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(exit)->texture);
        }
    } catch(...) { }
}

void help::prepareSprites(void *_eng)
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

void help::drawHelp(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;

        if (Sprites.size() == 0)
            prepareSprites(eng);
        eng->Graphics->clearScreen();
        eng->Graphics->drawObjects(Sprites);
        eng->Graphics->displayScreen();
    } catch(...) { }
}