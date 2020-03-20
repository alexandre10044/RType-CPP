/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Player
*/

#ifndef PLAYERM_HPP_
#define PLAYERM_HPP_

typedef struct  tPlayer {
    const int   id = 2;
    int         playerid;
    int         x;
    int         y;
    int         direction;
    int         health;
    int         score;
}               PlayerMessage;

#endif /* !PLAYERM_HPP_ */
