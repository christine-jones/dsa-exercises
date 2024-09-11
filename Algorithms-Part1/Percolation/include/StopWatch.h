/**
 * \file    StopWatch.h
 * \author  Christine Jones 
 * \brief   Very simple class that tracks and reports elapsed time in seconds.
 *
 * \copyright 2024
 * \license   GNU GENERAL PUBLIC LICENSE version 3 
 */

#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <chrono>

/**
 * Class that tracks and reports elapsed time in seconds.
 */
class StopWatch {

public:

    /**
     * Constructor. Starts the stopwatch at the current time.
     */
    StopWatch():
        m_start_time{Clock::now()}
    {}

    /**
     * Restarts the stopwatch at the current time.
     */
    void reset() { m_start_time = Clock::now(); }

    /**
     * Returns the elapsed time, in seconds, since the recorded start time.
     * 
     * \return double Elapsed time, in seconds.
     */
    double elapsed() const {
        return std::chrono::duration_cast<Second>(
                                        Clock::now() - m_start_time).count();
    }

private:

    using Clock  = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_start_time{};

};


#endif // STOP_WATCH_H
