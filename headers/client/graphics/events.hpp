/*
** EPITECH PROJECT, 2019
** events.hpp
** File description:
** events
*/

#ifndef EVENTS_HPP_
    #define EVENTS_HPP_

    #include <SFML/Graphics.hpp>

    #define INTEROP_LEN (14)

    class events {
        public:
            events();
            ~events();

            void handleEvent(sf::Event event, void *obj);
            void dispose();
            void (*interop[15])(sf::Event event, void *obj);
    };


#endif /* !EVENTS_HPP_ */