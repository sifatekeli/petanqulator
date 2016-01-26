// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Chrono.hpp"

double Chrono::elapsedRunning()
{
    _t1 = std::chrono::system_clock::now();
    return 1e-3 * std::chrono::duration_cast < std::chrono::milliseconds >
        (_t1 - _t0).count();
}

double Chrono::elapsedStopped() const
{
    return 1e-3 * std::chrono::duration_cast < std::chrono::milliseconds >
        (_t1 - _t0).count();
}

void Chrono::start()
{
    _t1 = _t0 = std::chrono::system_clock::now();
}

void Chrono::stop()
{
    _t1 = std::chrono::system_clock::now();
}

