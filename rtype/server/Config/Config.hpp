/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Config
*/

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Log.hpp"

class Config {
	public:
		Config();
		~Config();
        int     read(std::string file);
        void    print(std::string key = "");
	protected:
	private:
        std::map<std::string, std::string> config;
};

#endif /* !CONFIG_HPP_ */
