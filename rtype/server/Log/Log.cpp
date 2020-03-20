/*
** EPITECH PROJECT, 2019
** Log
** File description:
** Log
*/

#include "Log.hpp"

Log::Log() {};
Log::~Log() {};


/*
** Logs with color
*/
void Log::Console(std::string startColor, std::string message)
{
    std::cout << startColor << message << RESET << std::endl;
}
void Log::Console(std::string startColor, std::string head, std::string message)
{
    std::cout  << startColor << "[" << head << "] "<< message << RESET << std::endl;
}

/*
** Overloads for logs with head
*/
void Log::Error(std::string startColor, std::string head ,std::string message)
{
    std::cerr << startColor << "[" << head << "] " << message << RESET << std::endl;
}

void Log::Error(std::string startColor, std::string message)
{
    std::cerr << "[" << startColor << message << RESET << std::endl;
}