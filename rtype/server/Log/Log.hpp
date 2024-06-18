/*
** EPITECH PROJECT, 2019
** Log
** File description:
** Log
*/

#ifndef LOG_HPP_
#define LOG_HPP_
#include <map>
#include <string>
#include <iostream>

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[93m"
#define BG_YELLOW "\033[103m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

class Log {
	public:
        static void Console(std::string startColor, std::string message);
        static void Error(std::string startColor, std::string message);
        static void Console(std::string startColor, std::string head,std::string message);
        static void Error(std::string startColor, std::string head,std::string message);
    protected:
	private:
		Log();
		~Log();
};

#endif /* !LOG_HPP_ */
