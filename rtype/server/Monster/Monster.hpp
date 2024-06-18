/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Monster
*/

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include <utility>
#include <dlfcn.h>
#include <string>

class Monster {
	public:
		Monster(std::string lib_path);
		~Monster();

	protected:
	private:
        int                         _power;
        int                         _health;
        std::pair<float, float>     _position;
        float                       _speed_h;
        float                       _speed_w;
};

#endif /* !MONSTER_HPP_ */
