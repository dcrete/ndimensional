#pragma once

#include <functional>
#include "ndimensional/config.hpp"
#include "ndimensional/algorithm.hpp"

namespace nd::detail {

    template<class T, class Operation>
    struct operation {
        T _rhs;
        Operation _operation;

        constexpr operation(T&& rhs) noexcept
            : _rhs(std::forward<T>(rhs)),
            _operation(Operation{}) {
        }

        constexpr operation(Operation&& operation, T&& rhs) noexcept
            : _rhs(std::forward<T>(rhs)),
            _operation(std::forward<Operation>(operation)) {
        }

        template<class V>
        constexpr auto operator()(V&& lhs) const noexcept
            -> decltype(_operation(std::forward<V>(lhs), _rhs)) {
            return _operation(std::forward<V>(lhs), _rhs);
        }
    };
}

namespace nd {

    template<class Operation, class T>
    constexpr auto make_operator(Operation&& operation, T&& rhs) noexcept -> Operation {
        return Operation(std::forward<Operation>(operation), std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto equal_to(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::equal_to<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto not_equal_to(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::not_equal_to<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto less(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::less<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto less_equal(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::less_equal<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto greater(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::greater<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto greater_equal(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::greater_equal<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto plus(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::plus<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto minus(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::minus<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto multiplies(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::multiplies<>>;
        return operator_t(std::forward<T>(rhs));
    }

    template<class T>
    constexpr auto divides(T&& rhs) noexcept {
        using operator_t = detail::operation<T, std::divides<>>;
        return operator_t(std::forward<T>(rhs));
    }
}

namespace nd::operators {

    template<class T, class Value>
    constexpr T operator+(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return transform(left, plus(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr T operator-(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return transform(left, minus(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr T operator*(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return transform(left, multiplies(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr T operator/(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return transform(left, divides(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr bool operator==(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return all_of(left, equal_to(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr bool operator!=(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return all_of(left, not_equal_to(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr bool operator<(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return all_of(left, less(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr bool operator<=(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return all_of(left, less_equal(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr bool operator>(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return all_of(left, greater(static_cast<root_type<T>>(right)));
    }

    template<class T, class Value>
    constexpr bool operator>=(T left, Value right) noexcept {
        static_assert(is_convertible_root_type<T, Value>);
        return all_of(left, greater_equal(static_cast<root_type<T>>(right)));
    }
}