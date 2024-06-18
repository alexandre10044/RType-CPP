/*
** EPITECH PROJECT, 2019
** game.cpp
** File description:
** game
*/

#include <iostream>

#include "../../headers/client/game.hpp"
#include "../../headers/client/engine.hpp"

static sf::Clock PowerCl;

game::game(sf::Font _font)
{
    GameFont = _font;
    for (int i = 0; i < 100; i++)
        Keys.push_back(false);
    Time = 0;
}

game::~game()
{ }

void game::prepareText(void *_eng)
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

std::vector<game_object *> game::prepareSprites(void *_eng, std::vector<game_object *> tmp)
{
    static const std::string cant_find = "<Debug> Can't find resource.";
    engine *eng = (engine *)_eng;
    std::vector<game_object *> out;

    try {
        if (out.size() != 0)
            out.clear();
        for (unsigned int i = 0; i < tmp.size(); i++) {
            game_object *sp = tmp[i];
            entry *rsc = eng->Graphics->Rsc->getResource(sp->Name);

            if (rsc == NULL) {
                std::cout << cant_find << std::endl;
                continue;
            }
            sp->Id = out.size();
            sp->Sp.setTexture(rsc->texture, false);
            if (sp->Rect != 0) {
                sp->Sp.setTextureRect(sf::IntRect(sf::Vector2i((sp->Width / sp->Rect) * sp->Pos,
                (sp->Height / sp->Rect) * sp->Line), sf::Vector2i((sp->Width / sp->Rect),
                (sp->Height / sp->Rect))));
            }
            out.push_back(sp);
        }
    } catch(...) { }
    return (out);
}

void game::prepare(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;

        if (Sprites.size() == 0)
            Sprites = prepareSprites(eng, mainSpritesStep());
        if (GUI.size() == 0)
            GUI = prepareSprites(eng, mainGUIStep());
        if (Texts.size() == 0)
            prepareText(eng);
    } catch(...) { }
}

void game::drawGame(void *_eng)
{
    engine *eng = (engine *)_eng;

    try {
        scrollGame(eng);
        prepare(eng);
        keyEvents(_eng);
        checkForUpdate();
        eng->Graphics->clearScreen();
        eng->Graphics->drawObjects(Sprites);
        eng->Graphics->drawObjects(Monsters);
        eng->Graphics->drawObjects(Entities);
        eng->Graphics->drawObjects(GUI);
        for (unsigned int i = 0; i < Texts.size(); i++)
            if (i != 9 || (i == 9 &&
            PowerCl.getElapsedTime().asMilliseconds() >= POWER_DELAY))
                eng->Graphics->drawObject(Texts[i], false);
        eng->Graphics->displayScreen();
    } catch(...) { }
}

void game::dispose()
{
    Sprites.clear();
    Texts.clear();
    Keys.clear();
    GUI.clear();
    Entities.clear();
    Monsters.clear();
    Move = false;
    PowerCl.restart();
    Time = 0;
    Life = 3;
}