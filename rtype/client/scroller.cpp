/*
** EPITECH PROJECT, 2019
** scroller.cpp
** File description:
** scroller
*/

#include <iostream>

#include "../../headers/client/game.hpp"
#include "../../headers/client/engine.hpp"

static sf::Clock Cl;
static sf::Clock MonsterCl;
static sf::Clock GameCl;

static void scrollEnemies(engine *eng)
{
    static const std::string enemy = "enemy1.png";
    int y = rand() % 1000;
    int pos = rand() % 6;
    int line = rand() % 1;

    if (MonsterCl.getElapsedTime().asMilliseconds() > 3000) {
        game_object *sp = new game_object(eng->Game->Entities.size(),
            enemy, 1920, y, 236, 252, 7, line);
        entry *rsc = eng->Graphics->Rsc->getResource(sp->Name);

        if (rsc != NULL) {
            sp->Id = eng->Game->Monsters.size();
            sp->Pos = pos;
            sp->Type = West;
            sp->Sp.setTexture(rsc->texture, false);
            eng->Game->Monsters.push_back(sp);
        }
        MonsterCl.restart();
    }
}

static void updateRatios(engine *eng)
{
    double ratio = 1.0;

    if (eng->Game->Sprites.size() != 0 && Cl.getElapsedTime().asMilliseconds() > 10) {
        eng->Game->Sprites[0]->X -= 2;
        eng->Game->Sprites[1]->X -= 2;
        if (eng->Game->Sprites[1]->X <= 0) {
            eng->Game->Sprites[0]->X = 0;
            eng->Game->Sprites[1]->X = 1920;
        }
        for (unsigned int i = 0; i < eng->Game->Monsters.size(); i++) {
            eng->Game->Monsters[i]->X -= 3;
        }
        if (eng->Game->Sprites.size() != 2) {
            for (unsigned int i = 0; i < eng->Game->Monsters.size(); i++) {
                int index = 2;
                if (eng->Game->Sprites[index]->X >= eng->Game->Monsters[i]->X &&
                    eng->Game->Sprites[index]->X <= eng->Game->Monsters[i]->X + 50 &&
                    eng->Game->Sprites[index]->Y >= eng->Game->Monsters[i]->Y &&
                    eng->Game->Sprites[index]->Y <= eng->Game->Monsters[i]->Y + 50) {
                    if (std::atoi(eng->Game->Texts[0]->Name.c_str()) == 1) {
                        eng->Graphics->Window.create(sf::VideoMode(900, 506), WINDOW_TITLE);
                        eng->Graphics->RatioWidth = ratio;
                        eng->Graphics->RatioHeight = ratio;
                        eng->Step = MENU;
                    } else {
                        eng->Game->Texts[0]->Name = "\t" + std::to_string(std::atoi(eng->Game->Texts[0]->Name.c_str()) - 1);
                        eng->Game->Monsters.erase(eng->Game->Monsters.begin() + i);
                    }
                }
            }
        }
    Cl.restart();
    }
}

static void updateEntities(engine *eng)
{
    for (unsigned int i = 0; i < eng->Game->Entities.size(); i++) {
        if (eng->Game->Entities[i]->Type == West) {
            eng->Game->Entities[i]->X -= eng->Game->Entities[i]->Speed;
            if (eng->Game->Entities[i]->X <= 0) {
                eng->Game->Entities.erase(eng->Game->Entities.begin() + i);
                eng->Game->scrollGame(eng);
                return;
            }
        } else if (eng->Game->Entities[i]->Type == East) {
            eng->Game->Entities[i]->X += eng->Game->Entities[i]->Speed;
            if (eng->Game->Entities[i]->X >= 1920) {
               eng->Game-> Entities.erase(eng->Game->Entities.begin() + i);
                eng->Game->scrollGame(eng);
                return;
            }
                    
        }
    }
}

static void ajustSpeed(engine *eng)
{
    for (unsigned int i = 0; i < eng->Game->Monsters.size(); i++) {
        if (eng->Game->Monsters[i]->Type == West) {
            eng->Game->Monsters[i]->X -= eng->Game->Monsters[i]->Speed;
            if (eng->Game->Monsters[i]->X <= 0) {
                eng->Game->Monsters.erase(eng->Game->Monsters.begin() + i);
                eng->Game->scrollGame(eng);
                return;
            }
        } else if (eng->Game->Monsters[i]->Type == East) {
            eng->Game->Monsters[i]->X += eng->Game->Monsters[i]->Speed;
            if (eng->Game->Monsters[i]->X >= 1920) {
                eng->Game->Monsters.erase(eng->Game->Monsters.begin() + i);
                eng->Game->scrollGame(eng);
                return;
            }
                    
        }
    }
}

void game::scrollGame(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;

        scrollEnemies(eng);
        updateRatios(eng);
        ajustSpeed(eng);
        updateEntities(eng);
        if (GameCl.getElapsedTime().asMilliseconds() >= 1000
            && Texts.size() != 0) {
            Time++;
            Texts[2]->Name = "    " + std::to_string(Time);
            GameCl.restart();
        }

    } catch(...) { }
}

void game::checkForUpdate()
{
    try {
        std::vector<game_object *> out;

        for (int i = 0; i < 4; i++) {
            if (i == 0)
                out = Sprites;
            if (i == 1)
                out = GUI;
            if (i == 2)
                out = Entities;
            if (i == 3)
                out = Monsters;
            for (unsigned int i = 0; i < out.size(); i++) {
                game_object *sp = out[i];
                if (sp->Rect != 0) {
                    sf::IntRect tmpRect = sf::IntRect(sf::Vector2i((sp->Width / sp->Rect) * sp->Pos,
                        (sp->Height / sp->Rect) * sp->Line), sf::Vector2i((sp->Width / sp->Rect),
                        (sp->Height / sp->Rect)));
                    sf::IntRect curr = sp->Sp.getTextureRect();
                    if (curr.left != tmpRect.left ||
                        curr.top != tmpRect.top ||
                        curr.width != tmpRect.width ||
                        curr.height != tmpRect.height)
                        sp->Sp.setTextureRect(tmpRect);
                }
                if (sf::Vector2f(sp->X, sp->Y) != sp->Sp.getPosition())
                    sp->Sp.setPosition(sf::Vector2f(sp->X, sp->Y));
            }
        }
        if (Texts.size() != 0) {
            for (unsigned int i = 0; i < Texts.size(); i++) {
                if (sf::Vector2f(Texts[i]->X, Texts[i]->Y) != Texts[i]->Text.getPosition())
                    Texts[i]->Text.setPosition(sf::Vector2f(Texts[i]->X, Texts[i]->Y));
                if (Texts[i]->Text.getString() != sf::String(Texts[i]->Name))
                    Texts[i]->Text.setString(Texts[i]->Name);
            }
        }
    } catch(...) { }
}