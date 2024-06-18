/*
** EPITECH PROJECT, 2019
** menu.cpp
** File description:
** menu
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "../../../../headers/client/graphics/menu.hpp"
#include "../../../../headers/client/graphics/resources.hpp"
#include "../../../../headers/client/engine.hpp"

menu::menu()
{
    Step = Main;
}

menu::~menu()
{ }

std::vector<menu_sprite *> menu::mainStep()
{
    std::vector<menu_sprite *> sprites = {
        new menu_sprite(0, "bg.png", 0, 0),
        new menu_sprite(1, "audioMute.png", 10, 460)
    };
    return (sprites);
}

void menu::menuClick(int x, int y, void *_eng)
{
    static const std::string cant_found = "<Debug> Can't found resource.";
    static const std::string audio = "audio.png";
    static const std::string mute = "audioMute.png";

    try {
        engine *eng = (engine *)_eng;
        
        if (x >= 275 && x <= 413 &&
            y >= 216 && y <= 242) { // Play
            eng->Step = ROOMS;
        } else if (x >= 418 && x <= 604 &&
            y >= 244 && y <= 271) { // Help
            eng->Step = HELP;
        } else if (x >= 277 && x <= 419 &&
            y >= 270 && y <= 295) { // Settings
            eng->Step = SETTINGS;
        } else if (x >= 426 && x <= 601 &&
            y >= 299 && y <= 323) { // Exit
            eng->Step = EXIT;
            eng->Client->running = false;
        } else if (x >= 8 && x <= 46 &&
            y >= 456 && y <= 492) { // Sound
            if (eng->Music->inst.getStatus() == sf::SoundSource::Status::Playing) {
                entry *rsc = eng->Graphics->Rsc->getResource(audio);

                if (rsc == NULL) {
                    std::cout << cant_found << std::endl;
                    return;
                }
                eng->Music->Break();
                Sprites[1]->Sp.setTexture(rsc->texture);
            } else {
                entry *rsc = eng->Graphics->Rsc->getResource(mute);

                if (rsc == NULL) {
                    std::cout << cant_found << std::endl;
                    return;
                }
                eng->Music->Play();
                Sprites[1]->Sp.setTexture(rsc->texture);
            }
        }
    } catch(...) { }
}

void menu::menuForecast(int x, int y, void *_eng)
{
    static const std::string play = "bg_play.png";
    static const std::string help = "bg_help.png";
    static const std::string settings = "bg_settings.png";
    static const std::string exit = "bg_exit.png";
    static const std::string bg = "bg.png";
    int index = 0;

    try {
        engine *eng = (engine *)_eng;
        if (!Sprites.size())
            return;
        if (x >= 275 && x <= 413 &&
            y >= 216 && y <= 242) {
            if (!Sprites[index]->Name.compare(play))
                return;
            Sprites[index]->Name = play;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(play)->texture);
        } else if (x >= 418 && x <= 604 &&
            y >= 244 && y <= 271) {
            if (!Sprites[index]->Name.compare(help))
                return;
            Sprites[index]->Name = help;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(help)->texture);
        } else if (x >= 277 && x <= 419 &&
            y >= 270 && y <= 295) {
            if (!Sprites[index]->Name.compare(settings))
                return;
            Sprites[index]->Name = settings;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(settings)->texture);
        } else if (x >= 426 && x <= 601 &&
            y >= 299 && y <= 323) {
            if (!Sprites[index]->Name.compare(exit))
                return;
            Sprites[index]->Name = exit;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(exit)->texture);
        } else {
            if (!Sprites[index]->Name.compare(bg))
                return;
            Sprites[index]->Name = bg;
            Sprites[index]->Sp.setTexture(eng->Graphics->Rsc->getResource(bg)->texture);
        }
    } catch(...) { }
}

void menu::prepareSprites(void *_eng)
{
    static const std::string cant_found = "<Debug> Can't found resource.";

    try {
        engine *eng = (engine *)_eng;
        std::vector<menu_sprite *> tmp;

        Sprites.clear();
        if (eng->Graphics->Menu->Step == Main) {
            tmp = mainStep();
        }
        for (unsigned int i = 0; i < tmp.size(); i++) {
            menu_sprite *sp = tmp[i];
            entry *rsc = eng->Graphics->Rsc->getResource(sp->Name);

            if (rsc == NULL) {
                std::cout << cant_found << std::endl;
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

void menu::drawMenu(void *_eng)
{
    try {
    engine *eng = (engine *)_eng;

    if (!Sprites.size())
        prepareSprites(eng);
    eng->Graphics->clearScreen();
    for (unsigned int i = 0; i < Sprites.size(); i++)
        eng->Graphics->Window.draw(Sprites[i]->Sp);
    eng->Graphics->displayScreen();
    } catch(...) { }
}

void menu::dispose()
{
    Sprites.clear();
}