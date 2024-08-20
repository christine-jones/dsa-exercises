#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <chrono>

class StopWatch {

public:

    StopWatch():
        m_start_time{Clock::now()}
    {}

    void reset() { m_start_time = Clock::now(); }

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
