// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Game.hpp"

#include <map>

class Player 
{
    public:
        std::map<std::string, double> _params;
        virtual ~Player() = default;
        virtual ThrowParams chooseParams(const Game & game) = 0;
};

class PlayerRandom : public Player 
{
    protected:
        Prng _prng;
    public:
        virtual ThrowParams chooseParams(const Game & game) override;
};

class PlayerBestRandom : public PlayerRandom 
{
    public:
        PlayerBestRandom();
        virtual ThrowParams chooseParams(const Game & game) override;
};

#endif

