#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ratio>
#include <chrono>

namespace utility {

template<typename TRep = double, typename TPeriod = std::ratio<1, 1>>
class Timer final
{
public:
    Timer() = default;

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

    ~Timer() = default;

    void reset();
    TRep elapsed() const;
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimeUnit = std::chrono::duration<TRep, TPeriod>;

    std::chrono::time_point<Clock> begin_ {Clock::now()};
};


template<typename TRep, typename TPeriod>
void Timer<TRep, TPeriod>::reset()
{
    begin_ = Clock::now();
}


template<typename TRep, typename TPeriod>
TRep Timer<TRep, TPeriod>::elapsed() const
{
    return std::chrono::duration_cast<TimeUnit>(Clock::now() - begin_).count();
}

} // namespace utility

#endif // TIMER_HPP_