/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Attack
*/

#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include <utility>
#include <mutex>

class Attack {
	public:
		Attack(int x, int y);
		~Attack();
        void                setPower(int p);
        void                setSpeed(float s);
        void                setDimensions(int h, int w);
        int                 getPower();
        float               getSpeed();
        std::pair<int, int> getDimensions();
        std::pair<float, int> getPosition();
        void                setPosition(int h, int w);
	protected:
	private:
        std::mutex                  _attack_lock;
        int                         _power;
        int                         _height;
        int                         _width;
        // X then Y since Y wont change for now
        std::pair<float, int>       _position;
        float                       _speed_w;
};

#endif /* !ATTACK_HPP_ */
