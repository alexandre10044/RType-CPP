/*
** EPITECH PROJECT, 2019
** serverData.hpp
** File description:
** serverData
*/

#ifndef SERVERDATA_HPP_
    #define SERVERDATA_HPP_

    #include <string>

    class serverData {
        public:
            serverData(std::string _addr, int _port);
            ~serverData();

            void dispose();

            std::string Address;
            int Port;
    };


#endif /* !SERVERDATA_HPP_ */