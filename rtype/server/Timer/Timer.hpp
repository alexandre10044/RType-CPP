/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>
#include <chrono>
#include <ratio>

typedef std::chrono::high_resolution_clock game_clock;
class Timer {
	public:
		Timer();
		~Timer();
        void    start();
        void    stop();
        double  get_diff();
        double     get_ms();
        double     get_s();
	protected:
	private:
        bool                    _started;
        game_clock::time_point  _game_start;
        game_clock::time_point  _last_call;
};

#endif /* !TIMER_HPP_ */
