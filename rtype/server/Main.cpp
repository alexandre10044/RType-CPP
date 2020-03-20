/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Main
*/

#include "Log.hpp"
#include "Server.hpp"
#include "Config.hpp"

int main(int ac, char **av)
{
    int err = 0;
    Log::Console(BLUE BOLD, "Server", "Initializing");
    Server main_server;
    /*Config  config;

    config.read("./config.cfg");
    config.print();*/
    main_server.setPort(8083);
    if ((err = main_server.Init()) < 0) {
        Log::Error(RED BOLD, "Server", "Could not init server.");
        return (84);
    }
    Log::Console(GREEN BOLD, "Server", "Server initiated");
    main_server.Run();
    Log::Console(BOLD RED, "Server", "Closing server");
}