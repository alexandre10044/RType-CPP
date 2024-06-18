/*
** EPITECH PROJECT, 2019
** game_object.hpp
** File description:
** game_object
*/

#ifndef GAME_OBJECT_HPP_
    #define GAME_OBJECT_HPP_

    enum entity_kind {
        Object,
        Monster,
        Spatial,
        Player
    };

    enum entity_type {
        West,
        East,
        Unknow
    };

    class game_object {
        public:
            game_object(int _id, std::string _name, int _x, int _y,
                int _w = 0, int _h = 0, int _rect = 0, int _l = 0);
            ~game_object();

            int Id;
            int Width;
            int Height;
            int Pos;
            int Rect;
            int Line;
            int Speed;
            enum entity_kind Kind;
            enum entity_type Type;
            std::string Name;
            sf::Sprite Sp;
            sf::Text Text;
            int X, Y;
    };


#endif /* !GAME_OBJECT_HPP_ */