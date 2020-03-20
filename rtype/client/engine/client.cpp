/*
** EPITECH PROJECT, 2019
** client.cpp
** File description:
** client
*/

#include <iostream>

#include "../../../headers/client/engine/client.hpp"
#include "../../../headers/client/engine.hpp"
#include "../../server/Messages/Attack/AttackMessage.hpp"
#include "../../server/Messages/Monsters/MonstersMessage.hpp"
#include "../../server/Messages/Player/PlayerMessage.hpp"

client::client(void *_eng)
{
    tmp = _eng;
    running = false;
    Manager = new NetworkManager();
}

client::~client()
{ }

bool client::serverConnect()
{
    receiveLoop();
    return (true);
}

static void defineSocket(engine *eng)
{
    bzero(&eng->Client->servaddr, sizeof(eng->Client->servaddr));
    eng->Client->servaddr.sin_addr.s_addr = inet_addr(eng->Data->ServerData->Address.c_str());
    eng->Client->servaddr.sin_port = htons(eng->Data->ServerData->Port);
    eng->Client->servaddr.sin_family = AF_INET;

    eng->Client->l = sizeof(eng->Client->clientaddr);
    eng->Client->m = sizeof(eng->Client->servaddr);
    eng->Client->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    eng->Client->Manager->setFd(eng->Client->sockfd);
}

static void checkConnection(engine *eng)
{
    if(connect(eng->Client->sockfd, (struct sockaddr *)&eng->Client->servaddr, sizeof(eng->Client->servaddr)) < 0)
    {
        std::cout << "<Debug> Error : Connection Failed" << std::endl;
        eng->Client->running = false;
    }
    std::cout << "<Debug> Connected to server (" << eng->Data->ServerData->Address << ":" << std::to_string(eng->Data->ServerData->Port) << ")" << std::endl;
}

void *process(void *obj)
{
    try {
        engine *eng = (engine *)obj;

        defineSocket(eng);
        checkConnection(eng);
        while (eng->Client->running) {
            auto tmp = eng->Client->Manager->receiveFrom();
            char *buff = G1(tmp);
            int id = (*buff);

            AttackMessage *attackMsg;
            MonstersMessage *monstersMsg;
            PlayerMessage *playerMsg;
            (void)monstersMsg;

            switch (id)
            {
                case MessagesId::ATTACK:
                    attackMsg = reinterpret_cast<AttackMessage*>(buff);
                    eng->Client->handleAttack(eng, attackMsg);
                    break;
                case MessagesId::MONSTER:
                    monstersMsg = reinterpret_cast<MonstersMessage*>(buff);
                    std::cout << "Monster" << std::endl;
                    break;
                case MessagesId::PLAYER:
                    playerMsg = reinterpret_cast<PlayerMessage*>(buff);
                    eng->Client->handlePlayer(eng, playerMsg);
                    break;
                default:
                    break;
            }
        }
        close(eng->Client->sockfd);
    } catch(...) { }
    return (nullptr);
}

void client::receiveLoop()
{
    if (running)
        return;
    try {
    running = true;
    pthread_create(&this->thread, NULL, process, tmp);
    } catch(...) { }
}

void client::dispose()
{
    try {
    running = false;
    pthread_cancel(thread);
    } catch(...) { }
}

void client::handlePlayer(void *_eng, void *_playerMsg)
{  
    engine *eng = (engine *)_eng;
    PlayerMessage *playerMsg = (PlayerMessage *)_playerMsg;
    game_object *sp = NULL;
    entry *rsc = NULL;
    
    for (unsigned int i = 2; i < eng->Game->Sprites.size(); i++)
        if (eng->Game->Sprites[i]->Id == playerMsg->playerid) {
            sp = eng->Game->Sprites[i];
            break;
        }
    if (sp == NULL) {
        sp = new game_object(2, "r-typesheet42.png", playerMsg->x, playerMsg->y, 249, 129, 5, 0);
        rsc = eng->Graphics->Rsc->getResource(sp->Name);
        if (rsc == NULL) {
            std::cout << "<Debug> Can't find resource." << std::endl;
            return;
        }
        sp->Id = playerMsg->playerid;
        sp->Pos = 1;
        sp->Type = East;
        sp->Sp.setTexture(rsc->texture, false);
        eng->Game->Sprites.push_back(sp);
    } else {
        sp->X = playerMsg->x;
        sp->Y = playerMsg->y;
    }
    std::cout << "Player " << playerMsg->playerid << " " << playerMsg->x << " " << playerMsg->y << std::endl;
}

void client::handleAttack(void *_eng, void *_attackMsg)
{

    engine *eng = (engine *)_eng;
    AttackMessage *attackMsg = (AttackMessage *)_attackMsg;
    game_object *sp = NULL;
    entry *rsc = NULL;

    if (attackMsg->x > 1920 || attackMsg->y > 1008
        || attackMsg->x < 0 || attackMsg->y < 0) {
        eng->Game->Entities.clear();
        return;
    }
    for (unsigned int i = 0; i < eng->Game->Entities.size(); i++)
        if (eng->Game->Entities[i]->Id == attackMsg->attackid)
            sp = eng->Game->Entities[i];
    if (sp == NULL) {
        if (attackMsg->speed == 8) {
            sp = new game_object(eng->Game->Entities.size(),
            "friendlyEntity2.png", attackMsg->x, attackMsg->y, 324, 64, 4, 0);
        } else {
            sp = new game_object(eng->Game->Entities.size(),
            "friendlyEntity1.png", attackMsg->x, attackMsg->y, 131, 48, 4, 0);
        }
        rsc = eng->Graphics->Rsc->getResource(sp->Name);
        if (rsc == NULL) {
            std::cout << "<Debug> Can't find resource." << std::endl;
            return;
        }
        sp->Id = attackMsg->attackid;
        sp->Pos = 1;
        sp->Type = East;
        sp->Sp.setTexture(rsc->texture, false);
        eng->Game->Entities.push_back(sp);

    } else {
        for (unsigned int i = 0; i < eng->Game->Monsters.size(); i++) {
            if (eng->Game->Monsters[i]->X >= attackMsg->x &&
                eng->Game->Monsters[i]->X <= attackMsg->x + 50 &&
                eng->Game->Monsters[i]->Y >= attackMsg->y &&
                eng->Game->Monsters[i]->Y <= attackMsg->y + 50) {
                eng->Game->Texts[1]->Name = "\t" + std::to_string(std::atoi(eng->Game->Texts[1]->Name.c_str()) + 10);
                eng->Game->Monsters.erase(eng->Game->Monsters.begin() + i);
                break;
            }
        }
        sp->X = attackMsg->x;
        sp->Y = attackMsg->y;
    }

    std::cout << "Attack " << std::to_string(attackMsg->attackid) << " " << std::to_string(attackMsg->speed) << " " <<
        std::to_string(attackMsg->x) << " " << std::to_string(attackMsg->y) << std::endl;
}