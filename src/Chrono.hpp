
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
