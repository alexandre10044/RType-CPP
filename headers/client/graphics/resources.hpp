/*
** EPITECH PROJECT, 2019
** resources.hpp
** File description:
** resources
*/

#ifndef RESOURCES_HPP_
    #define RESOURCES_HPP_

    #include <SFML/Graphics.hpp>

    #include <string>
    #include <vector>

    class entry {
        public:
            entry() { };

            std::string name;
            std::string path;
            sf::Texture texture;
            sf::Image image;
    };

    class resources {
        private:
            void loadDirectory(const std::string dirPath);
        public:
            resources();
            ~resources();

            void dispose();
            void loadResources();
            entry *getResource(std::string _name);
            std::vector<entry *> Entries;
    };

#endif /* !RESOURCES_HPP_ */