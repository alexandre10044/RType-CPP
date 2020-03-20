/*
** EPITECH PROJECT, 2019
** data.hpp
** File description:
** data
*/

#ifndef DATA_HPP_
    #define DATA_HPP_

    #include "../data/serverData.hpp"

    class data {
        public:
            data(std::string _addr, int _port);
            ~data();

            void dispose();

            serverData *ServerData;
    };

#endif /* !DATA_HPP_ */