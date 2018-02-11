#pragma once

#include <random>
#include "ndimensional/config.hpp"
#include "ndimensional/algorithm.hpp"
#include "ndimensional/array.hpp"
#include "ndimensional/functional.hpp"

#define TEST_METHOD(x) static constexpr auto x()

namespace nd::tests {

    using root_type = double;
    using array_type = array<root_type, 5, 3, 4>;

    static constexpr auto make_zeros() noexcept {
        return array_type{};
    }

    static constexpr auto make_ones() noexcept {
        return assign(make_zeros(), 1.0);
    }

    template<class T>
    constexpr bool is_same_root_type = std::is_same_v<root_type, nd::root_type<T>>;

    template<class T> struct distribution;
    template<> struct distribution<double> { using type = std::uniform_real_distribution<>; };
    template<> struct distribution<int> { using type = std::uniform_int_distribution<>; };
    template<> struct distribution<size_t> { using type = std::uniform_int_distribution<>; };
    template<class T> using distribution_t = typename distribution<T>::type;

    template<class T>
    class random_generator {
        std::random_device rd{};
        std::mt19937_64 eng{ rd() };
        distribution_t<T> dist{ T{ 1 }, T{ 9 } };

    public:
        constexpr auto operator()() {
            auto result = dist(eng);
            if constexpr (std::is_same_v<T, size_t>) {
                return static_cast<size_t>(result);
            }
            else {
                return result;
            }
        }
    };
}