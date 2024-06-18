/*
** EPITECH PROJECT, 2019
** inst.cpp
** File description:
** music
*/

// # Lib Imports

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>

// # Local Imports

#include "../../headers/client/music.hpp"

// # Static values

static const char *music_path = "resources/audio.wav";
static const char *music_error = "Can't load inst.wav.";

// # Builder / Destructor

music::music()
{
    if (!inst.openFromFile(music_path))
        std::cout << music_error << std::endl;
    inst.setVolume(20);
}

music::~music(void)
{
}

// # Public Methods

void music::Play(void)
{
    if (inst.getStatus() == sf::SoundSource::Status::Playing)
        return;
    inst.play();
    inst.setLoop(true);
}

void music::Break(void)
{
    inst.pause();
}

void music::Stop(void)
{
    inst.stop();
}