#ifndef RAND_HPP_
#define RAND_HPP_

#include <random>
#include <ctime>
#include <limits>
#include <cstdint>
#include <type_traits>
#include <string>
#include <cassert>


namespace utility {

/*
 * Rand a integer within the specificed range using Mersenne Twister algorithm.
 */
template<typename T = int>
T rand(std::int_fast64_t min = 0,
       std::int_fast64_t max = std::numeric_limits<T>::max());


template<typename T>
T rand(const std::int_fast64_t min, const std::int_fast64_t max)
{
    static_assert(std::is_integral<T>::value, "T must be integral");
    assert(max <= std::numeric_limits<T>::max());
    assert(min >= 0);
    assert(min <= max);

    static std::mt19937 mt {
        static_cast<std::mt19937::result_type>(std::time(nullptr))
    };

    if (min == max) {
        return min;
    }

    T num {};
    std::uniform_int_distribution dist {0, 255};

    for (size_t i = 0; i < sizeof(T); ++i) {
        num <<= 8;
        num |=  dist(mt);
    }

    // for a signed type set the most significant
    // bit to 0 in order to avoid a negative number
    if (std::is_signed<T>::value) {
        num &= ~(1 << (sizeof(T) * 8 - 1));
    }

    return min + (num % (max - min));
}

};

#endif // RAND_HPP_
