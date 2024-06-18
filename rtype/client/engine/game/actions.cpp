/*
** EPITECH PROJECT, 2019
** gameActions.cpp
** File description:
** gameActions
*/

#include <iostream>

#include "../../../../headers/client/game.hpp"
#include "../../../../headers/client/engine.hpp"
#include "../../../server/Messages/Attack/AttackMessage.hpp"
#include "../../../server/Messages/Monsters/MonstersMessage.hpp"
#include "../../../server/Messages/Player/PlayerMessage.hpp"

static sf::Clock ShootCl;
static sf::Clock PowerCl;
static sf::Clock MoveCl;

static int normal_speed = 6;
static int bonus_speed = 8;
static int bonus_delay = 500;
static int flags = 0;

static int handleActionDelay(engine *eng)
{
    static const int fail = -1;
    int elapsed = ShootCl.getElapsedTime().asMilliseconds();
    int speed = normal_speed;

    if (eng->Game->Sprites.size() == 2)
        return (fail);
    if (elapsed <= bonus_delay)
        return (fail);
    ShootCl.restart();
    if (elapsed >= POWER_DELAY) {
        PowerCl.restart();
        speed = bonus_speed;
     } else {
        speed = normal_speed;
    }
    return (speed);
}

static int minimum_speed = 0;

void game::shootEvent(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;
        game_object *player = eng->Game->Sprites[2];
        int speed = handleActionDelay(eng);

        if (speed < minimum_speed)
            return;
        AttackMessage *msg = new AttackMessage();
        msg->x = (int)player->X;
        msg->y = (int)player->Y;
        msg->speed = speed;
        sendto(eng->Client->sockfd, msg, sizeof(*msg), flags,
            (struct sockaddr *)&eng->Client->servaddr,eng->Client->m);
        delete(msg);
    } catch(...) { }
}

static int north_dir = 1;
static int south_dir = 10;
static int west_dir = 100;
static int east_dir = 1000;

static void handleMovements(engine *eng)
{
        PlayerMessage *msg = new PlayerMessage();
        static const int minimum = 2;
        static const int up_pos_decal = 4;
        int index = 2;

        if (eng->Game->Keys[sf::Keyboard::Up]) {
            if (eng->Game->Move == false)
                eng->Game->Move = true;
            if (eng->Game->Sprites.size() != minimum)
                eng->Game->Sprites[index]->Pos = up_pos_decal;
            MoveCl.restart();
            msg->direction = north_dir;
            sendto(eng->Client->sockfd, msg, sizeof(*msg), flags,
                (struct sockaddr *)&eng->Client->servaddr, eng->Client->m);
        } else if (eng->Game->Keys[sf::Keyboard::Down]) {
            if (eng->Game->Move == false)
                eng->Game->Move = true;
            if (eng->Game->Sprites.size() != minimum)
                eng->Game->Sprites[index]->Pos = minimum;
            MoveCl.restart();
            msg->direction = south_dir;
            sendto(eng->Client->sockfd, msg, sizeof(*msg), flags,
                (struct sockaddr *)&eng->Client->servaddr, eng->Client->m);
        } else if (eng->Game->Keys[sf::Keyboard::Left]) {
            if (eng->Game->Move == false)
            eng->Game->Move = true;
            msg->direction = west_dir;
            sendto(eng->Client->sockfd, msg, sizeof(*msg), flags,
                (struct sockaddr *)&eng->Client->servaddr, eng->Client->m);
        } else if (eng->Game->Keys[sf::Keyboard::Right]) {
            if (eng->Game->Move == false)
            eng->Game->Move = true;
            msg->direction = east_dir;
            sendto(eng->Client->sockfd, msg, sizeof(*msg), flags,
                (struct sockaddr *)&eng->Client->servaddr, eng->Client->m);
        }
}

void game::keyEvents(void *_eng)
{
    try {
        engine *eng = (engine *)_eng;
        PlayerMessage *msg = new PlayerMessage();
        static const int refresh = 100;
        unsigned int index = 2;
        int start = 0;

        if (eng->Game->Keys[sf::Keyboard::Up] || eng->Game->Keys[sf::Keyboard::Down] ||
            eng->Game->Keys[sf::Keyboard::Left] || eng->Game->Keys[sf::Keyboard::Right])
            handleMovements(eng);
        else if (Move == true && MoveCl.getElapsedTime().asMilliseconds() > refresh) {
            if (Sprites.size() != index)
                Sprites[index]->Pos = start;
            msg->direction = start;
            sendto(eng->Client->sockfd, msg, sizeof(*msg), flags,
                (struct sockaddr *)&eng->Client->servaddr, eng->Client->m);
            Move = false;
        }
        if (Keys[sf::Keyboard::Space])
            shootEvent(eng);
        if (msg != NULL)
            delete(msg);
    } catch(...) { }
}