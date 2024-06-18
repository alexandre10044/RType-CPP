/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Config
*/

#include "Config.hpp"

Config::Config()
{
}

int     Config::read(std::string file)
{
    std::ifstream   stream(file);

    if (!stream) {
        Log::Error(BOLD RED, "Config", "Coult not read config.");
        return (-1);
    }
    while (stream) {
        std::string line;
        std::string elem;
        std::string key;
        std::string value;
        std::getline(stream, line);
        if (line[0] == '#')
            continue;
        std::stringstream   stream_s(line);
        if (std::getline(stream_s, elem, '='))
            key = elem;
        if (std::getline(stream_s, elem, '='))
            value = elem;
        if (key != "") {
            config[key] = elem;
            Log::Console(BLUE BOLD, "Config", "Read [" + key + "] -> " + value);
        }
    }
    return (0);
}

void        Config::print(std::string key)
{
    if (key == "")
    {
        for (auto const& x : config) {
            if (x.first != "")
                std::cout << "[" << x.first << "] -> " << x.second << std::endl;
        }
    }
    else
    {

    }

}

Config::~Config()
{
}
