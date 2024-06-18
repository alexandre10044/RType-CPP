/*
** EPITECH PROJECT, 2019
** resources.cpp
** File description:
** resources
*/

#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <algorithm>

#include "../../../../headers/client/graphics/resources.hpp"

resources::resources()
{ }

resources::~resources()
{ }

void resources::dispose()
{
    try {
    for (unsigned int i = 0; i < Entries.size(); i++)
        Entries[i]->texture.~Texture();
    Entries.clear();
    } catch(...) { }
}

void resources::loadDirectory(const std::string dirPath)
{
    try {
        for (const auto & _path : std::experimental::filesystem::directory_iterator(dirPath)) {
            try {
                std::ostringstream oss;
                oss << _path;
                std::string path = oss.str();
                path.erase(std::remove(path.begin(), path.end(), '\"'), path.end());
                entry *ent = new entry();

                std::size_t dotPos = path.rfind('.');
                std::size_t sepPos = path.rfind('/');
                if(sepPos == std::string::npos)
                    continue;
                ent->name = path.substr(sepPos + 1, sepPos + (dotPos - sepPos) + 1);
                ent->path = path;
                if (!ent->image.loadFromFile(path)) {
                    std::cout << "<Debug> Can't load image file : " << ent->name << std::endl;
                    continue;
                }
                if (!ent->texture.loadFromImage(ent->image)) {
                    std::cout << "<Debug> Can't load texture file : " << ent->name << std::endl;
                    continue;
                }
                Entries.push_back(ent);
            } catch (...) {
                std::cout << "<Debug> Can't load resource file : " << dirPath << std::endl;
                continue;
            }
        }
        std::cout << "<Debug> Resources folder \"" << dirPath << "\" loaded successfully." << std::endl; 
    } catch(...) { }
}

void resources::loadResources()
{
    try {
        std::string path = "resources/";

        loadDirectory(path + "bgs");
        loadDirectory(path + "gifs");
        loadDirectory(path + "buttons");
        loadDirectory(path + "panels");
        loadDirectory(path + "entities");
    } catch(...) { }
}

entry *resources::getResource(std::string _name)
{
    try {
        for (unsigned int i = 0; i < Entries.size(); i++)
            if (Entries[i]->name.compare(_name) == 0)
                return (Entries[i]);
        } catch(...) { }
    return (NULL);
}