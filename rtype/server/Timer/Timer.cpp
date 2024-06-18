/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Timer
*/

#include "Timer.hpp"

Timer::Timer()
{

}

Timer::~Timer()
{
}

// Return the nanoseconds passed since the start of the game
double  Timer::get_diff() {
    if (_started == false)
        return (0.0);
    double s = (((_last_call = game_clock::now()) - _game_start ).count());
    _game_start = game_clock::now();
    return s;
}

double  Timer::get_ms() {
    if (_started == false)
        return (0.0);
    return (this->get_diff() / 1000000.0);
}

double  Timer::get_s() {
    if (_started == false)
        return (0.0);
    return (this->get_diff() / 1000000000.0);
}

void    Timer::start()
{
    _started = true;
    _game_start = game_clock::now();
}

void    Timer::stop()
{
    _started = false;
}