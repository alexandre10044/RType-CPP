/*
** EPITECH PROJECT, 2019
** Code Workspace Epitech (Workspace)
** File description:
** Server
*/

#include "Server.hpp"

#define G0(n) std::get<0>(n)
#define G1(n) std::get<1>(n)
#define G2(n) std::get<2>(n)


int         loop_read(Server *main_server)
{
    for (std::string line; std::getline(std::cin, line);) {
        // IO
        if (line == "exit")
            exit(0);
        std::cout << line << std::endl;
    }
    return (0);
}

int         main_loop(Server *main_server, Client *owner)
{
    bool    client_exited = false;
    sockaddr_in *sock = (sockaddr_in*)owner->getClientAddress();
    std::string address = inet_ntoa(sock->sin_addr);
    Log::Console(BLUE, address, "New client.");
    while (!client_exited)
    {
        NetworkManager      *srv = main_server->getNetworkManager();
        MessageQueue        queue = owner->getQueue();
        if (queue.size() > 0) {
            char                *buff = queue.front().first;
            int                 size = queue.front().second;
            int                 id = (*buff);
            Attack              *_new;
            AttackMessage       *atk;
            PlayerMessage       *ply;

            owner->popQueue();
            switch (id)
            {
                case (int)(MessagesId::ATTACK):
                    if (size < sizeof(AttackMessage))
                        break;
                    Log::Console(GREEN, address, "New attack.");
                    atk = reinterpret_cast<AttackMessage*>(buff);
                    // New attack from client
                    _new = new Attack(atk->x, atk->y);
                    _new->setSpeed(atk->speed);
                    main_server->setAttacks(_new);
                    break;
                case (int)(MessagesId::PLAYER):
                    Log::Console(GREEN, address, "New movement.");
                    if (size < sizeof(PlayerMessage))
                        break;
                    ply = reinterpret_cast<PlayerMessage*>(buff);
                    // Movement from client
                    bool    top, bot, left, right;
                    top = (bool)(ply->direction % 10);
                    ply->direction /= 10;
                    bot = (bool)(ply->direction % 10);
                    ply->direction /= 10;
                    left = (bool)(ply->direction % 10);
                    ply->direction /= 10;
                    right = (bool)(ply->direction % 10);
                    ply->direction /= 10;
                    if (!top and !bot and !left and !right)
                        owner->setDirection(directions::NONE);
                    else if (top and !bot)
                        owner->setDirection(directions::TOP);
                    else if (bot and !top)
                        owner->setDirection(directions::BOT);
                    else if (left and !right)
                        owner->setDirection(directions::LEFT);
                    else if (right and !left)
                        owner->setDirection(directions::RIGHT);
                    break;
                default:
                    ErrorMessage msg;
                    srv->sendTo((char*)&msg, sizeof(msg), (sockaddr_in){0}, 0);
                    break;
            }
            if (buff)
                delete buff;
        }
    }
    main_server->removeClient(owner);
    Log::Error(RED BOLD, "Client Thread", "Client exited");
    return (0);
}

Server::~Server()
{

}

std::vector<Attack*>            Server::getAttacks()
{
    return (_attacks);
}

NetworkManager  *Server::getNetworkManager()
{
    return (_manager);
}

std::mutex  *Server::getLock()
{
    return (&_server_lock);
}

int     Server::removeClient(Client *c)
{
    _server_lock.lock();
    std::vector<Client*>::iterator e;
    for (e = _clients.begin(); e != _clients.end(); e++)
    {
        if (c == (*e)) {
            _clients.erase(e);
            return (0);
        }
    }
    return (1);
    _server_lock.unlock();
}

Server::Server()
{
    _second_elapsed = 0;
}

void    Server::setPort(unsigned int port)
{
    _port = port;
}

int     Server::Init()
{
    int error = 0;

    if (_manager->init(&_server_addr, _port, &_fd) < 0)
        return (-1);
    return (1);
}

void    Server::setAttacks(Attack* a)
{
    _server_lock.lock();
    _attacks.push_back(a);
    _server_lock.unlock();
}

int Server::Run()
{
    int     err = 0;
    bool    shouldrun = true;

    fcntl(_fd, F_SETFL, O_NONBLOCK, 0);
    _time.start();
    Log::Console(BG_YELLOW BLACK BOLD, "Info", "Started on :" + std::to_string(_port));
    _manager = new NetworkManager();
    _manager->setFd(_fd);
    std::thread loop_r(loop_read, this);
    while (shouldrun) {
        // Game logic ?
        usleep(1000);
        auto                                        received = _manager->receiveFrom();
        bool                                        create = true;
        if (G2(received) > 0) {
            for (Client *c : _clients)
            {
                if (strncmp(c->getClientAddress()->sa_data, G0(received)->sa_data, 14) == 0)
                {
                    create = false;
                    c->pushQueue(G1(received), G2(received));
                }
            }
            if (create && G2(received) > 0)
            {
                Client *newC = new Client(G0(received));
                newC->pushQueue(G1(received), G2(received));
                _clients.push_back(newC);
                std::thread     client(main_loop, this, newC);
                _threads.push_back(std::move(client));
                //_threads[_threads.size() - 1].join();
            }
        }
        updateGame();
    }
    return (0);
}

void    Server::updateGame()
{
    float   second_elapsed = _second_elapsed;

    if (second_elapsed < (1.0/120.0)) {
        _second_elapsed += _time.get_s();
        return;
    }

    // Nanos ?
    //std::cout << ""<< second_elapsed  << "/s" << std::endl;

    int i = 0;
    // Attacks movements ?
    for (auto e = _attacks.begin(); e < _attacks.end(); e++)
    {
        auto position = (*e)->getPosition();
        position.first += (((float)(*e)->getSpeed()) * (640.0 / 6.0) * second_elapsed);

        if (position.first > 1920 || position.first < 0) {
            // Attack ended (too far ?) (for monsters too)
            Log::Console(RED, "Server", "Attack " + std::to_string(i) + " vanished");
            AttackMessage *test = new AttackMessage();
            test->speed = 0;
            test->x = -1;
            test->y = -1;
            test->attackid = i;
            for (Client *c : _clients)
            {
                sockaddr_in *s = (sockaddr_in*)c->getClientAddress();
                _manager->sendTo((char*)test,sizeof(*test), *s, (socklen_t)(sizeof(*c->getClientAddress())));
            }
            delete *e;
            _attacks.erase(e);
            if (test)
                delete test;
            continue;
        }
        else {
            (*e)->setPosition(position.first, position.second);
            AttackMessage *test = new AttackMessage();
            test->speed = (*e)->getSpeed();
            test->x = (*e)->getPosition().first;
            test->y = (*e)->getPosition().second;
            test->attackid = i;
            for (Client *c : _clients)
            {
                sockaddr_in *s = (sockaddr_in*)c->getClientAddress();
                _manager->sendTo((char*)test,sizeof(*test), *s, (socklen_t)(sizeof(*c->getClientAddress())));
            }
            if (test)
                delete test;
        }
        i++;
    }
    second_elapsed += _time.get_s();
    i = 0;
    for (Client *c : _clients)
    {
        auto position = c->getPosition();
        switch (c->getDirection())
        {
            case directions::NONE:
            break;
            case directions::BOT:
            if (position.second < 1008)
                position.second += c->getSpeedH() * 32.0 * second_elapsed;
            else
                position.second = 1008;
            break;
            case directions::TOP:
            if (position.second > 0)
                position.second -= c->getSpeedH() * 32.0 * second_elapsed;
            else
                position.second = 0;
            break;
            case directions::RIGHT:
            if (position.first < 1700)
                position.first += c->getSpeedW() * 64.0 * second_elapsed;
            else
                position.first = 1700;
            break;
            case directions::LEFT:
            if (position.first > 0)
                position.first -= c->getSpeedW() * 64.0 * second_elapsed;
            else
                position.first = 0;
            break;
            default:
            break;
        }
        c->setPosition(position.first, position.second);
        PlayerMessage *test = new PlayerMessage();
        test->playerid = i;
        test->x = (c)->getPosition().first;
        test->y = (c)->getPosition().second;
        for (Client *c : _clients)
        {
            sockaddr_in *s = (sockaddr_in*)c->getClientAddress();
            _manager->sendTo((char*)test,sizeof(*test), *s, (socklen_t)(sizeof(*c->getClientAddress())));
        }
        delete test;
        i++;
    }
    second_elapsed += _time.get_s();
    for (Monster *m : _monsters)
    {

    }
    _second_elapsed = 0.0;
}
