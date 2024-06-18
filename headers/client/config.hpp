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

class config {
	public:
		config();
		~config();
        int     read(std::string file);
        void    print(std::string key = "");
	private:
        std::map<std::string, std::string> data;
};

#endif /* !CONFIG_HPP_ */
