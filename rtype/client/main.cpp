/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main
*/

#include <vector>
#include <iostream>
#include <string.h>

#include "../../headers/client/engine.hpp"

static const int normal_exit = 0;
static const int error_exit = 84;

void help(char **av)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t" << av[0] << " address port" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\taddress\taddress of the server" << std::endl;
    std::cout << "\tport\tport of the server" << std::endl;
}

void failure()
{
    std::cout << "Invalid usage, use -h or -help to get more informations." << std::endl;
}

std::vector<std::string> split(const std::string& str, char delim)
{
	auto i = 0;
	std::vector<std::string> list;
	auto pos = str.find(delim);
	
    try {
        while (pos != std::string::npos)  {
            list.push_back(str.substr(i, pos - i));
            i = ++pos;
            pos = str.find(delim, pos);
        }
        list.push_back(str.substr(i, str.length()));
    } catch(...) { }
	return (list);
}

bool syntax(std::string address, std::string port)
{
    static const std::string syntax = "[0123456789]";
	std::vector<std::string> parts;

    try {
        if (address.compare("localhost") == 0)
            address = "127.0.0.1";
        parts = split(address, '.');;
        if (parts.size() != 4)
            return (false);
        for (std::string str : parts) {
            if (!(!str.empty() && (str.find_first_not_of(syntax) == std::string::npos))
            || stoi(str) > 255 || stoi(str) < 0)
                return (false);
        }
        if (!(!port.empty() && (port.find_first_not_of(syntax))))
            return (false);
    } catch(...) { return (false); }
	return (true);
}

int main(int ac, char **as)
{
    engine *eng;

    try {
        if (ac >= 2 && (!strcmp(as[1], "-h") || !strcmp(as[1], "-help")))
            return (help(as), normal_exit);
        if (ac < 3)
            return (failure(), error_exit);
        if (!syntax(std::string(as[1]), std::string(as[2])))
            return (failure(), error_exit);
        std::string addr = std::string(as[1]);
        std::string port = std::string(as[2]);
        eng = new engine(addr, std::stoi(port));
        eng->run();
        eng->abort();
        //eng->dispose();
    } catch(...) { }
    return (normal_exit);
}