/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Attack
*/

#include "Attack.hpp"

Attack::Attack(int x, int y) {
    if (!_attack_lock.try_lock())
        return;
    _position = std::pair<float, int>(x, y);
    _attack_lock.unlock();
}

Attack::~Attack() {
}

std::pair<float, int>     Attack::getPosition() {
    return (_position);
}

void    Attack::setPosition(int h, int w) {
    if (!_attack_lock.try_lock())
        return;
    _position = std::pair<int, int>(h, w);
    _attack_lock.unlock();
}

void    Attack::setPower(int p) {
    if (!_attack_lock.try_lock())
        return;
    _power = p;
    _attack_lock.unlock();
}

void    Attack::setSpeed(float s) {
    if (!_attack_lock.try_lock())
        return;
    _speed_w = s;
    _attack_lock.unlock();
}

void    Attack::setDimensions(int h, int w) {
    if (!_attack_lock.try_lock())
        return;
    _height = h;
    _width = w;
    _attack_lock.unlock();
}

int                 Attack::getPower() {
    return (_power);
}

float               Attack::getSpeed() {
    return (_speed_w);
}

std::pair<int, int> Attack::getDimensions() {
    return (std::pair<int, int>(_width, _height));
}