/*
** EPITECH PROJECT, 2019
** settings.cpp
** File description:
** settings
*/

#include <iostream>

#include "../../../../headers/client/graphics/settings.hpp"
#include "../../../../headers/client/engine.hpp"

static std::vector<game_object *> Sprites;
static std::vector<game_object *> Texts;

settings::settings(sf::Font _font)
{
    GameFont = _font;
    Fps = 60;
    Sound = 20;
    Quality = 2;
}

settings::~settings()
{

}

void settings::dispose()
{
    Sprites.clear();
    Texts.clear();
}

std::vector<game_object *> settings::mainStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "settingsPanel.png", 0, 0),
        new game_object(1, "exitButton.png", 740, 10),
    };
    return (sprites);
}

std::vector<game_object *> settings::mainTextStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "60", 618, 123),
        new game_object(1, "20", 618, 178),
        new game_object(2, "High", 608, 233),
    };
    return (sprites);
}

void settings::checkForUpdate()
{
    try {
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

void settings::settingsClick(int x, int y, void *_eng)
{
    try {
    std::vector<std::string> values = {
        std::string("Low"),
        std::string("Medium"),
        std::string("High")
    };
    engine *eng = (engine *)_eng;

    if (x >= 744 && x <= 885 &&
        y >= 15 && y <= 68) {
        eng->Step = MENU;
    }

    if (x >= 476 && x <= 494 &&
        y >= 125 && y <= 138) { // - FPS
        if (Fps == 0)
            return;
        Fps--;
        Texts[0]->Name = std::to_string(Fps);
    } else if (x >= 476 && x <= 494 &&
        y >= 179 && y <= 197) { // - Sound
        if (Sound == 0)
            return;
        Sound--;
        eng->Music->inst.setVolume(Sound);
        Texts[1]->Name = std::to_string(Sound);
    } else if (x >= 476 && x <= 494 &&
        y >= 234 && y <= 252) { // - Graphics
        if (Quality == 0)
            Quality = 3;
        Quality--;
        Texts[2]->Name = values[Quality];
    } else if (x >= 763 && x <= 781 &&
        y >= 123 && y <= 140) { // + FPS
        if (Fps == 120)
            return;
        Fps++;
        Texts[0]->Name = std::to_string(Fps);
    } else if (x >= 763 && x <= 781 &&
        y >= 176 && y <= 193) { // + Sound
        if (Sound == 100)
            return;
        Sound++;
        eng->Music->inst.setVolume(Sound);
        Texts[1]->Name = std::to_string(Sound);
    } else if (x >= 763 && x <= 781 &&
        y >= 234 && y <= 252) { // + Graphics
        if (Quality == 2)
            Quality = -1;
        Quality++;
        Texts[2]->Name = values[Quality];
    }
    } catch(...) { }
}

void settings::settingsForecast(int x, int y, void *_eng)
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

void settings::prepareSprites(void *_eng)
{
    try {
    engine *eng = (engine *)_eng;
    std::vector<game_object *> tmp = mainStep();

    Sprites.clear();
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

void settings::prepareText(void *_eng)
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

void settings::drawSettings(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;

        if (Sprites.size() == 0)
            prepareSprites(eng);
        if (Texts.size() == 0)
            prepareText(eng);
        checkForUpdate();
        eng->Graphics->clearScreen();
        eng->Graphics->drawObjects(Sprites);
        eng->Graphics->drawObjects(Texts, false);
        eng->Graphics->displayScreen();
    } catch(...) { }
}