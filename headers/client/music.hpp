/*
** EPITECH PROJECT, 2019
** music.hpp
** File description:
** music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_

    #include <SFML/Audio.hpp>

    // # Class

    class music {
        public:
            music();
            ~music(void);

            void Play(void);
            void Break(void);
            void Stop(void);
            sf::Music inst;
        private:
            void *engine;
    };

#endif /* !MUSIC_HPP_ */