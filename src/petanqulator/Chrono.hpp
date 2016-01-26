// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _CHRONO_HPP_
#define _CHRONO_HPP_

#include <chrono>

class Chrono 
{
    private:
        typedef std::chrono::time_point<std::chrono::system_clock> Time;
        Time _t0;
        Time _t1;

    public:
        void start();
        void stop();
        double elapsedStopped() const;
        double elapsedRunning();
};

#endif
