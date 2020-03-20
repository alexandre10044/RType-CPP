/*
** EPITECH PROJECT, 2019
** gameStep.cpp
** File description:
** gameStep
*/

#include <iostream>

#include "../../../../headers/client/game.hpp"
#include "../../../../headers/client/engine.hpp"

static std::string error_find = "<Debug> Can't found resource.";
static std::string audio = "audio.png";
static std::string audioMute = "audioMute.png";

void game::gameClick(int x, int y, void *_eng)
{
    static const double ratio = 1.0;
    int index = 3;

    try {
        engine *eng = (engine *)_eng;
        
        if (x >= 1687 && x <= 1830 &&
            y >= 13 && y <= 69) {
            eng->Graphics->Window.create(sf::VideoMode(900, 506), WINDOW_TITLE);
            eng->Graphics->RatioWidth = ratio;
            eng->Graphics->RatioHeight = ratio;
            eng->Step = MENU;
        } else if (x >= 1803 && x <= 1847 &&
            y >= 946 && y <= 979) { // Sound
            if (eng->Music->inst.getStatus() == sf::SoundSource::Status::Playing) {
                entry *rsc = eng->Graphics->Rsc->getResource(audio);

                if (rsc == NULL) {
                    std::cout << error_find << std::endl;
                    return;
                }
                eng->Music->Break();
                GUI[index]->Sp.setTexture(rsc->texture);
            } else {
                entry *rsc = eng->Graphics->Rsc->getResource(audioMute);

                if (rsc == NULL) {
                    std::cout << error_find << std::endl;
                    return;
                }
                eng->Music->Play();
                GUI[index]->Sp.setTexture(rsc->texture);
            }
        }
    } catch(...) { }
}

static std::string exit_button = "exitButton.png";
static std::string exitEffect_button = "exitEffectButton.png";

void game::gameForecast(int x, int y, void *_eng)
{
    int current = 2;

    try {
        engine *eng = (engine *)_eng;
        if (GUI.size() == 0)
            return;
        if (x >= 1687 && x <= 1830 &&
            y >= 13 && y <= 69) {
            if (!GUI[current]->Name.compare(exitEffect_button))
                return;
            GUI[current]->Name = exitEffect_button;
            GUI[current]->Sp.setTexture(eng->Graphics->Rsc->getResource(exitEffect_button)->texture);
        } else {
            if (!GUI[current]->Name.compare(exit_button))
                return;
            GUI[current]->Name = exit_button;
            GUI[current]->Sp.setTexture(eng->Graphics->Rsc->getResource(exit_button)->texture);
        }
    } catch(...) { }
}