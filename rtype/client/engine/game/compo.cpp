/*
** EPITECH PROJECT, 2019
** gameComponents.cpp
** File description:
** gameComponents
*/

#include "../../../../headers/client/game.hpp"
#include "../../../../headers/client/engine.hpp"

std::vector<game_object *> mainGUIStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "playersPanel.png", 10, 10),
        new game_object(1, "statsPanel.png", 10, 880),
        new game_object(2, "exitButton.png", 1685, 10),
        new game_object(3, "audioMute.png", 1810, 950),
    };
    return (sprites);
}

std::vector<game_object *> mainSpritesStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "bg_game.png", 0, 0),
        new game_object(1, "bg_game.png", 1920, 0)
    };
    return (sprites);
}

std::vector<game_object *> mainTextStep()
{
    std::vector<game_object *> sprites = {
        new game_object(0, "    3", 98, 916),
        new game_object(1, "    0", 98, 933),
        new game_object(2, "    0", 98, 952),
        new game_object(3, "PLAYER 1", 135, 58),
        new game_object(4, "0", 135, 78),
        new game_object(5, "PLAYER 2", 135, 113),
        new game_object(6, "0", 135, 133),
        new game_object(7, "PLAYER 3", 135, 169),
        new game_object(8, "0", 135, 189),
        new game_object(9, "/!\\ BOOST AVAILABLE", 55, 237),
    };
    return (sprites);
}