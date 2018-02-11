#pragma once

#include "ndimensional/config.hpp"

namespace nd::detail {
	
    template<class T>
    struct iterator {
        T& source;
        size_t begin = 0U;
        size_t current = 0U;
        size_t max = 0U;

        constexpr iterator(T& values, size_t offset, size_t count) noexcept
            : source(values),
            begin(offset),
            current(offset),
            max(count + offset) {
        }

        constexpr auto operator*() const noexcept
            -> decltype(source.at(current)) {
            static_assert(std::is_const_v<T>);
            return source.at(current);
        }

        constexpr auto operator*() noexcept
            -> decltype(source.at(current)) {
            return source.at(current);
        }

        constexpr iterator& operator++() noexcept {
            ++current;
            return *this;
        }

        constexpr iterator operator+(int offset) noexcept {
            auto temp = *this;
            temp.current += offset;
            return temp;
        }

        constexpr bool operator==(const iterator& rhs) const noexcept {
            return (current = rhs.current);
        }

        constexpr bool operator!=(const iterator& rhs) const noexcept {
            return !this->operator==(rhs);
        }

        constexpr operator bool() const noexcept {
            return (current < max);
        }
    };
}

namespace nd {

    template<class Iterator>
    constexpr auto distance(Iterator it) noexcept -> size_t {
        return (it.current - it.begin);
    }

    template<class T>
    constexpr auto iterate(T& items, size_t offset = 0, size_t count = size_v<T>) noexcept -> detail::iterator<T> {
        return detail::iterator<T>(items, offset, count - offset);
    }

}